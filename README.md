NeuralStyle Plugin
====================

This plugin effect transfers style of `style image` to `content image` using neural network.

The mode files of neural network are not contained in this repository.
You have to get [nin_imagenet.caffemodel](https://gist.github.com/mavenlin/d802a5849de39225bcc6) and [VGG_ILSVRC_16_layers.caffemodel](https://gist.github.com/ksimonyan/211839e770f7b538e2d8#file-readme-md).

## How to install

### Windows

#### w/ GPU

0. install `Visual Studio 2013`
 * [link1](https://www.visualstudio.com/en-US/downloads/download-visual-studio-vs.aspx)
0. install `CUDA Toolkit 7.5` (Windows x86_64)
 * [link2](https://developer.nvidia.com/cuda-downloads)
0. install `cuDNN v4 Library for Windows`
 * [link3](https://developer.nvidia.com/rdp/cudnn-download)
 * copy `bin`, `include`, and `lib` directories to `C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v7.5`.
0. install `Python 2.7 WIndows 64-bit`
 * [link4](https://www.continuum.io/downloads)
0. install `openopt`
 * exec `pip install openopt` on command prompt
0. install `cvxopt`
 * download `cvxopt-1.1.7+openblas-cp27-none-win_amd64.whl` from [link5](http://www.lfd.uci.edu/~gohlke/pythonlibs/#cvxopt)
 * exec `pip install cvxopt-1.1.7+openblas-cp27-none-win_amd64.whl` on command prompt
0. install `chainer`
 * exec
   ```
   set VS100COMNTOOLS=%VS120COMNTOOLS%
   set PATH=%VS120COMNTOOLS%\..\..\VC\bin;%PATH%
   pip install chainer
   ```
   on command prompt
0. copy `neural_style_synthesizer` directory and `DWANGO_NeuralStyle.plugin` to `${path-to-stuff}/plugins`
0. copy `nin_imagenet.caffemodel` and `VGG_ILSVRC_16_layers.caffemodel` to `${path-to-stuff}/plugins/neural_style_synthesizer`

お疲れ様でした。

#### w/o GPU 

0. install `Python 2.7 WIndows 64-bit`
 * [link4](https://www.continuum.io/downloads)
0. install `openopt`
 * exec `pip install openopt` on command prompt
0. install `cvxopt`
 * download `cvxopt-1.1.7+openblas-cp27-none-win_amd64.whl` from [link5](http://www.lfd.uci.edu/~gohlke/pythonlibs/#cvxopt)
 * exec `pip install cvxopt-1.1.7+openblas-cp27-none-win_amd64.whl` on command prompt
0. install `chainer`
 * exec
   ```
   set VS100COMNTOOLS=%VS120COMNTOOLS%
   set PATH=%VS120COMNTOOLS%\..\..\VC\bin;%PATH%
   pip install chainer
   ```
   on command prompt
0. copy `neural_style_synthesizer` directory and `DWANGO_NeuralStyle.plugin` to `${path-to-stuff}/plugins`
0. copy `nin_imagenet.caffemodel` and `VGG_ILSVRC_16_layers.caffemodel` to `${path-to-stuff}/plugins/neural_style_synthesizer`
