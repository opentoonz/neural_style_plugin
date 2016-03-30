NeuralStyle Plugin
====================

This plugin effect transfers style of `style image` to `content image` using neural network.

The model files of neural networks are not contained in this repository.
You can get them from [nin_imagenet.caffemodel](https://gist.github.com/mavenlin/d802a5849de39225bcc6) and [VGG_ILSVRC_16_layers.caffemodel](https://gist.github.com/ksimonyan/211839e770f7b538e2d8#file-readme-md).

## How to install

### OS X

TBD

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
 * exec ```set VS100COMNTOOLS=%VS120COMNTOOLS%` ; set PATH=%VS120COMNTOOLS%\..\..\VC\bin;%PATH%` ; pip install chainer``` on command prompt
0. copy `neural_style_synthesizer` directory and `DWANGO_NeuralStyle.plugin` to `${path-to-stuff}/plugins`
0. copy `nin_imagenet.caffemodel` and `VGG_ILSVRC_16_layers.caffemodel` to `${path-to-stuff}/plugins/neural_style_synthesizer`

#### w/o GPU 

0. install `Python 2.7 WIndows 64-bit`
 * [link4](https://www.continuum.io/downloads)
0. install `openopt`
 * exec `pip install openopt` on command prompt
0. install `cvxopt`
 * download `cvxopt-1.1.7+openblas-cp27-none-win_amd64.whl` from [link5](http://www.lfd.uci.edu/~gohlke/pythonlibs/#cvxopt)
 * exec `pip install cvxopt-1.1.7+openblas-cp27-none-win_amd64.whl` on command prompt
0. install `chainer`
 * exec ```pip install chainer``` on command prompt
0. copy `neural_style_synthesizer` directory and `DWANGO_NeuralStyle.plugin` to `${path-to-stuff}/plugins`
0. copy `nin_imagenet.caffemodel` and `VGG_ILSVRC_16_layers.caffemodel` to `${path-to-stuff}/plugins/neural_style_synthesizer`

## How to use

### input ports

| port name | |
| --- | --- |
| `Content` | content image |
| `Style`   | style image |

### parameters

| param name | default value | min value | max value | |
| --- | ---:| ---:| ---:| --- |
| `xsplit`         |  1.000 |  1 |   16.0 | the number of horizontal splits |
| `ysplit`         |  1.000 |  1 |   16.0 | the number of vertical splits |
| `resize`         |  1.000 |  0 |    1.0 | resize factor: 1 (original size), 0.5 (half size), 0.1 (1/10 size), and so on. |
| `iteration`      | 10.000 |  0 | 1000.0 | the number of iterations for style optimization |
| `method`         |  1.000 |  0 |    1.0 | method flag for neural network: `{0: max_pooling, 1: average_pooling}`. The default value is recommended. |
| `model`          |  0.000 |  0 |    1.0 | model of neural network: `{0: nin, 1: vgg}`, `nin` is a small and `vgg` is a large model (*) |
| `smooth`         |  0.000 |  0 |    1.0 | sequential processing flag: `{0: off, 1: on}` (*) |
| `optimize`       |  1.000 |  0 |    1.0 | optimal selection flag for splited style images: `{0: off, 1: on}`. The default value is recommended. |
| `gpu`            | -1.000 | -1 |    3.0 | GPU id (CPUs are used when `gpu` euqals to `-1`) |
| `content_weight` |  0.005 |  0 |    0.1 | style weight of `Content` image |
| `pause`          |  0.000 |  0 |    1.0 | do-not-automatically-close-consoles flag for debugging: `{0: off, 1: on}` (only for Windows) |

(*) You have to set `Dedicated CPUs` to `Single` at `Preview Settings` and `Output Settings`, when you use the `vgg` model or enable the `smooth` flag.

The first execution is time-consuming, because the plugin generates a cache of the neural network models.
