NeuralStyle Plugin
====================

本プラグインは、ニューラルネットワークを利用して、スタイル画像の画風をコンテンツ画像に転写するエフェクトです。

ニューラルネットワークのモデルファイルは同梱していないので、動作させるためには、 [nin_imagenet.caffemodel](https://gist.github.com/mavenlin/d802a5849de39225bcc6) および [VGG_ILSVRC_16_layers.caffemodel](https://gist.github.com/ksimonyan/211839e770f7b538e2d8#file-readme-md) を入手してください。

## インストール

### OS X

TBD

### Windows

本プラグインを Windows 上で動作させるためには、下記の環境設定が必要になります。

#### GPU を使う場合

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
 * コマンドプロンプトから ```set VS100COMNTOOLS=%VS120COMNTOOLS%` ; set PATH=%VS120COMNTOOLS%\..\..\VC\bin;%PATH% ; pip install chainer``` を実行します。
0. `neural_style_synthesizer` ディレクトリと `DWANGO_NeuralStyle.plugin` を `${path-to-stuff}/plugins` にコピーする
0. `${path-to-stuff}/plugins/neural_style_synthesizer` に `nin_imagenet.caffemodel` と `VGG_ILSVRC_16_layers.caffemodel` をコピーする

お疲れ様でした。

#### GPU を使わない場合

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
0. `neural_style_synthesizer` ディレクトリと `DWANGO_NeuralStyle.plugin` を `${path-to-stuff}/plugins` にコピーする
0. `${path-to-stuff}/plugins/neural_style_synthesizer` に `nin_imagenet.caffemodel` と `VGG_ILSVRC_16_layers.caffemodel` をコピーする

## マニュアル

### 入力ポート

| ポート名 | 説明 |
| --- | --- |
| `Content` | コンテンツ画像 |
| `Style`   | スタイル画像 |

### パラメータ

| パラメータ名 | デフォルト値 | 最小値 | 最大値 | 説明 |
| --- | ---:| ---:| ---:| --- |
| `xsplit`         |  1.000 |  1 |   16.0 | 横方向の画面の分割数 |
| `ysplit`         |  1.000 |  1 |   16.0 | 縦方向の画面の分割数 |
| `resize`         |  1.000 |  0 |    1.0 | 画面のリサイズ: そのまま 1, 半分 0.5, 十分の一 0.1 など |
| `iteration`      | 10.000 |  0 | 1000.0 | 最適化の反復回数 |
| `method`         |  1.000 |  0 |    1.0 | `{0: max_pooling, 1: average_pooling}`。通常、デフォルト値から変更する必要はありません |
| `model`          |  0.000 |  0 |    1.0 | `{0: nin, 1: vgg}`。`nin` が軽量なモデルで、`vgg` が大きいモデルです (※) |
| `smooth`         |  0.000 |  0 |    1.0 | `{0: off, 1: on}`。連番処理をするかのフラグ (※) |
| `optimize`       |  1.000 |  0 |    1.0 | `{0: off, 1: on}`、分割したスタイルを最適化するかのフラグ。通常、デフォルト値から変更する必要はありません |
| `gpu`            | -1.000 | -1 |    3.0 | 利用する GPU 番号 (-1 は CPU を意味します) |
| `content_weight` |  0.005 |  0 |    0.1 | `Content` のスタイルを残す重み |
| `pause`          |  0.000 |  0 |    1.0 | デバッグ用に実行時に表示されるコンソールを開いたままにする (Windows 専用) |

※ `vgg` のような大きいモデルを使う場合や、`smooth` フラグで連番処理する場合は、必ず `プレビュー設定` と `出力設定` の `使用 CPU 数` を `1 つ` に設定してください。

モデルファイルのキャッシュを生成するために、初期起動時は時間がかかります。
