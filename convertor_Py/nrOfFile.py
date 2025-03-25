import os
import sys

from PIL import Image

if(len(sys.argv)>1):
    input_folder_path= sys.argv[1]
    tempfile=sys.argv[2]
    input_files=os.listdir(input_folder_path)
    a=str(len(input_files))
    with open(tempfile, "w",encoding="utf-8") as f:
        f.write(a)
