import os
import sys

from PIL import Image

if(len(sys.argv) > 1):
    input_folder_path= sys.argv[1]
    input_files=os.listdir(input_folder_path)

    output_folder_path=sys.argv[2]
    output_files=os.listdir(output_folder_path)

    for file in output_files:
        file_path = os.path.join(output_folder_path, file)
        os.remove(file_path)

    index=0

    for file in input_files:
        image=Image.open(os.path.join(input_folder_path,file))
        path=os.path.join(output_folder_path,f"fire{index}.bmp")
        image.save(path,format="bmp")
        index+=1

