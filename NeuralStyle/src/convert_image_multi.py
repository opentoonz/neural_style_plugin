import argparse
import shutil
import time

parser = argparse.ArgumentParser()
parser.add_argument("content_image")
parser.add_argument("texture_image")
parser.add_argument("--output_image", required=True)
parser.add_argument("--content_weight", type=float, default=0.005)
parser.add_argument("--gpu", type=int, default=-1)
parser.add_argument("--iteration", type=int, default=1000)
parser.add_argument("--xsplit", type=int, default=1)
parser.add_argument("--ysplit", type=int, default=1)
parser.add_argument("--resize", type=int, default=300,
                    help="maximum size of height and width for content and texture images")
parser.add_argument("--out_dir", required=True)
parser.add_argument("--no_optimize", dest="optimize", action="store_false")
args = parser.parse_args()

shutil.copyfile(args.content_image, args.output_image)
