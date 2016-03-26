NeuralStyle Plugin
====================


ニューラルネットワークのモデルファイルは同梱していないので、動作させるためには、 [nin_imagenet.caffemodel](https://gist.github.com/mavenlin/d802a5849de39225bcc6) および [VGG_ILSVRC_16_layers.caffemodel](https://gist.github.com/ksimonyan/211839e770f7b538e2d8#file-readme-md) を `neural_style_synthesizer` ディレクトリに配置してください。

## Windows で動作させる

本プラグインを Windows 上で動作させるためには、下記の環境設定が必要になります。

### GPU を使う場合

0. `Visual Studio Community 2013` をインストールする
 * [link1](https://www.visualstudio.com/ja-jp/downloads/download-visual-studio-vs.aspx) から Web インストーラをダウンロードして実行します
0. `CUDA Toolkit 7.5` をインストールする
 * [link2](https://developer.nvidia.com/cuda-downloads) で `Windows` `x86_64` を選択して、インストーラをダウンロード、実行します
0. `cuDNN` をインストールする
 * [link3](https://developer.nvidia.com/rdp/cudnn-download) から、ライセンスに同意後、`cuDNN v4 Library for Windows` をダウンロードします
 * 解凍してできる `bin`, `include`, `lib` ディレクトリを `C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v7.5` 以下に、上書きコピーします
0. `Python` をインストールする
 * [link4](https://www.continuum.io/downloads) から `PYTHON 2.7` の Windows 64-bit 版をダウンロードして、インストールします
0. `openopt` をインストールする
 * コマンドプロンプトから `pip install openopt` を実行します
0. `cvxopt` をインストールする
 * [link5](http://www.lfd.uci.edu/~gohlke/pythonlibs/#cvxopt) から `cvxopt-1.1.7+openblas-cp27-none-win_amd64.whl` をダウンロードします
 * コマンドプロンプトから `pip install cvxopt-1.1.7+openblas-cp27-none-win_amd64.whl` を実行します
0. `chainer` をインストールする
 * コマンドプロンプトから
   ```
   set VS100COMNTOOLS=%VS120COMNTOOLS%
   set PATH=%VS120COMNTOOLS%\..\..\VC\bin;%PATH%
   pip install chainer
   ```
   を実行します。
0. `neural_style_synthesizer` ディレクトリを `DWANGO_NeuralStyle.plugin` があるディレクトリにコピーする

お疲れ様でした。


### GPU を使わない場合

0. `Python` をインストールする
 * [link4](https://www.continuum.io/downloads) から `PYTHON 2.7` の Windows 64-bit 版をダウンロードして、インストールします
0. `openopt` をインストールする
 * コマンドプロンプトから `pip install openopt` を実行します
0. `cvxopt` をインストールする
 * [link5](http://www.lfd.uci.edu/~gohlke/pythonlibs/#cvxopt) から `cvxopt-1.1.7+openblas-cp27-none-win_amd64.whl` をダウンロードします
 * コマンドプロンプトから `pip install cvxopt-1.1.7+openblas-cp27-none-win_amd64.whl` を実行します
0. `chainer` をインストールする
 * コマンドプロンプトから ```pip install chainer``` を実行します
 * CUDA Toolkit がインストールされていると、実行に失敗する場合があります。その際は、上記の GPU を使う場合の手順を試すか、CUDA Toolkit をアンインストールしてください。
0. `neural_style_synthesizer` ディレクトリを `DWANGO_NeuralStyle.plugin` があるディレクトリにコピーする
