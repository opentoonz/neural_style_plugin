#define TNZU_DEFINE_INTERFACE
#include <toonz_utility.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <atomic>
#include <mutex>

class MyFx : public tnzu::Fx {
 public:
  //
  // PORT
  //
  enum {
    PORT_CONTENT,
    PORT_STYLE,
    PORT_COUNT,
  };

  int port_count() const override { return PORT_COUNT; }

  char const* port_name(int i) const override {
    static std::array<char const*, PORT_COUNT> names = {
        "Content", "Style",
    };
    return names[i];
  }

  //
  // PARAM GROUP
  //
  enum {
    PARAM_GROUP_DEFAULT,
    PARAM_GROUP_COUNT,
  };

  int param_group_count() const override { return PARAM_GROUP_COUNT; }

  char const* param_group_name(int i) const override {
    static std::array<char const*, PARAM_GROUP_COUNT> names = {
        "Default",
    };
    return names[i];
  }

  //
  // PARAM
  //
  enum {
    PARAM_XSPLIT,
    PARAM_YSPLIT,
    PARAM_RESIZE,
    PARAM_ITERATION,
    PARAM_METHOD,
    PARAM_MODEL,
    PARAM_SMOOTH,
    PARAM_OPTIMIZE,
    PARAM_GPU,
    PARAM_CONTENT_WEIGHT,
    PARAM_PAUSE,
    PARAM_COUNT,
  };

  int param_count() const override { return PARAM_COUNT; }

  ParamPrototype const* param_prototype(int i) const override {
    static std::array<ParamPrototype, PARAM_COUNT> const params = {
        ParamPrototype{"xsplit", PARAM_GROUP_DEFAULT, 1, 1, 16},
        ParamPrototype{"ysplit", PARAM_GROUP_DEFAULT, 1, 1, 16},
        ParamPrototype{"resize", PARAM_GROUP_DEFAULT, 1, 0, 1},
        ParamPrototype{"iteration", PARAM_GROUP_DEFAULT, 10, 0, 1000},
        ParamPrototype{"method", PARAM_GROUP_DEFAULT, 1, 0, 1},
        ParamPrototype{"model", PARAM_GROUP_DEFAULT, 0, 0, 1},
        ParamPrototype{"smooth", PARAM_GROUP_DEFAULT, 0, 0, 1},
        ParamPrototype{"optimize", PARAM_GROUP_DEFAULT, 1, 0, 1},
        ParamPrototype{"gpu", PARAM_GROUP_DEFAULT, -1, -1, 3},
        ParamPrototype{"content_weight", PARAM_GROUP_DEFAULT, 0.005, 0, 0.1},
        ParamPrototype{"pause", PARAM_GROUP_DEFAULT, 0, 0, 1},
    };
    return &params[i];
  }

 public:
  int end_render() override {
    std::lock_guard<std::mutex> lock(mutex_);
    for (auto&& file : history_) {
      remove(file.c_str());
    }
    history_.clear();
    return 0;
  }

  int enlarge(Config const& config, Params const& params,
              cv::Rect2d& retrc) override {
    retrc = tnzu::make_infinite_rect<double>();
    return 0;
  }

  int compute(Config const& config, Params const& params, Args const& args,
              cv::Mat& retimg) override try {
    DEBUG_PRINT(__FUNCTION__);
    if (args.invalid(PORT_STYLE)) {
      if (args.valid(PORT_CONTENT)) {
        tnzu::draw_image(retimg, args.get(PORT_CONTENT),
                         args.offset(PORT_CONTENT));
      }
      return 0;
    }

    if (args.invalid(PORT_CONTENT)) {
      if (args.valid(PORT_STYLE)) {
        tnzu::draw_image(retimg, args.get(PORT_STYLE), args.offset(PORT_STYLE));
      }
      return 0;
    }

    // params
    cv::Size const size = retimg.size();
    int const xsplit = params.get<int>(PARAM_XSPLIT);
    int const ysplit = params.get<int>(PARAM_YSPLIT);
    int const resize =
        params.get<int>(PARAM_RESIZE, std::max(size.width, size.height));
    int const iteration = params.get<int>(PARAM_ITERATION);
    bool const method = params.get<bool>(PARAM_METHOD);
    bool const model = params.get<bool>(PARAM_MODEL);
    bool const smooth = params.get<bool>(PARAM_SMOOTH);
    bool const optimize = params.get<bool>(PARAM_OPTIMIZE);
    int const gpu = params.get<int>(PARAM_GPU);
    double const content_weight = params.get<double>(PARAM_CONTENT_WEIGHT);
    bool const pause = params.get<bool>(PARAM_PAUSE);

    std::string const out_dir =
#ifdef _WIN32
        "C:/TEMP/"
#else
        "/tmp/"
#endif
        ;

    std::string content;
    {
      std::ostringstream out;
      out << out_dir << port_name(PORT_CONTENT) << "[" << config.frame
          << "].png";
      content = out.str();
    }

    std::string style;
    {
      std::ostringstream out;
      out << out_dir << port_name(PORT_STYLE) << "[" << config.frame << "].png";
      style = out.str();
    }

    std::string output;
    {
      cv::Mat const& content_img = args.get(PORT_CONTENT);
      cv::Mat const& style_img = args.get(PORT_STYLE);

      std::uint64_t const content_hash = tnzu::hash(content_img);
      std::uint64_t const style_hash = tnzu::hash(style_img);

      std::ostringstream out;
      out << out_dir << tnzu::plugin_info()->name << '[' << config.frame
          << "]{C{w=" << content_img.cols << ",h=" << content_img.rows
          << ",t=" << content_img.type() << ",n=" << content_hash << "}"
          << ",S{w=" << style_img.cols << ",h=" << style_img.rows
          << ",t=" << style_img.type() << ",n=" << style_hash << "}"
          << ",w=" << retimg.cols << ",h=" << retimg.rows
          << ",t=" << retimg.type() << ",x=" << xsplit << ",y=" << ysplit
          << ",r=" << resize << ",i=" << iteration << ",p=" << method
          << ",m=" << model << ",s=" << smooth << ",c=" << content_weight
          << "}.png";
      output = out.str();
    }

    std::string init_image;
    if (smooth) {
      std::lock_guard<std::mutex> lock(mutex_);
      if (!history_.empty()) {
        init_image = history_.back();
      }
    }

    std::string command_line;
    {
      std::ostringstream out;
#ifdef _WIN32
      out << "pushd \"%VS120COMNTOOLS%/../../VC\" & vcvarsall.bat amd64 & popd "
             "& pushd \"" << Fx::get_stuff_dir()
          << "/plugins/neural_style_synthesizer\" & ";
#endif
      out << "python bin/convert_image_multi.py"
          << " --iteration=" << iteration << " --gpu=" << gpu
          << " --xsplit=" << xsplit << " --ysplit=" << ysplit << " \""
          << content << "\" \"" << style << "\""
          << " --model=" << (model ? "vgg" : "nin") << " --output_image=\""
          << output << "\" --out_dir=\"" << out_dir << "\""
          << " --content_weight=" << content_weight;
      if (resize > 0) {
        out << " --resize=" << resize;
      }
      if (method) {
        out << " --average_pooling";
      }
      if (smooth && !init_image.empty()) {
        out << " --init_image=\"" << init_image << '\"';
      }
      if (!optimize) {
        out << " --no_optimize";
      }
#ifdef _WIN32
      out << " & popd";
      if (pause) {
        out << " & pause";
      }
#endif
      command_line = out.str();
    }
    DEBUG_PRINT(command_line.c_str());

    tnzu::draw_image(retimg, args.get(PORT_CONTENT), args.offset(PORT_CONTENT));

    if (!tnzu::file_exists(output.c_str())) {
      try {
        cv::imwrite(content, retimg);
      } catch (std::runtime_error const& e) {
        DEBUG_PRINT("failed to save a content image: " << e.what());
        return 0;
      }

      try {
        cv::imwrite(style, args.get(PORT_STYLE));
      } catch (std::runtime_error const& e) {
        DEBUG_PRINT("failed to save a style image: " << e.what());
        remove(content.c_str());
        return 0;
      }

      if (gpu >= 0) {
        std::lock_guard<std::mutex> lock(mutexes_[gpu]);
        system(command_line.c_str());
      } else {
        system(command_line.c_str());
      }

      remove(content.c_str());
      remove(style.c_str());
    }

    cv::Mat src = cv::imread(output);

    if ((src.cols <= 0) || (src.rows <= 0)) {
      DEBUG_PRINT("failed to load a output image");
      return 0;
    }

    cv::resize(src, src, size);

    if (retimg.type() == CV_8UC4) {
      for (int y = 0; y < size.height; ++y) {
        cv::Vec3b const* s = src.ptr<cv::Vec3b>(y);
        cv::Vec4b* d = retimg.ptr<cv::Vec4b>(y);
        for (int x = 0; x < size.width; ++x) {
          d[x][0] = s[x][0];
          d[x][1] = s[x][1];
          d[x][2] = s[x][2];
          // without an alpha channel
        }
      }
    } else {
      for (int y = 0; y < size.height; ++y) {
        cv::Vec3b const* s = src.ptr<cv::Vec3b>(y);
        cv::Vec4w* d = retimg.ptr<cv::Vec4w>(y);
        for (int x = 0; x < size.width; ++x) {
          d[x][0] = s[x][0] << 8;
          d[x][1] = s[x][1] << 8;
          d[x][2] = s[x][2] << 8;
          // without an alpha channel
        }
      }
    }

    {
      // register history
      std::lock_guard<std::mutex> lock(mutex_);
      history_.push_back(output);
    }

    return 0;
  } catch (cv::Exception const& e) {
    DEBUG_PRINT(e.what());
  }

 private:
  std::mutex mutex_;
  std::vector<std::string> history_;

  std::array<std::mutex, 4> mutexes_;
};

namespace tnzu {
PluginInfo const* plugin_info() {
  static PluginInfo const info(TNZU_PP_STR(PLUGIN_NAME),    // name
                               TNZU_PP_STR(PLUGIN_VENDOR),  // vendor
                               "",                          // note
                               "http://dwango.co.jp/");     // helpurl
  return &info;
}

Fx* make_fx() { return new MyFx(); }
}
