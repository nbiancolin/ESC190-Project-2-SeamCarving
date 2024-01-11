from PIL import Image
import sys

def write_image(image, filename):
    height = image.height
    width = image.width

    f = open(filename, "wb")

    f.write(height.to_bytes(2, byteorder='big'))
    f.write(width.to_bytes(2, byteorder='big'))
    img_raster = []
    for i in range(height):
        for j in range(width):
            img_raster.extend(image.getpixel((j, i))[:3])

    f.write(bytearray(img_raster))
    f.close()

def read_2bytes(f):
    bytes = f.read(2) # [int(f.read(1)), int(f.read(1))]
    return int.from_bytes(bytes, byteorder = 'big')


def read_image(filename):
    f = open(filename, "rb")
    height = read_2bytes(f)
    width = read_2bytes(f)
    image = Image.new("RGB", (width, height))
    bytes = f.read()
    for i in range(height):
        for j in range(width):
            image.putpixel((j, i), (bytes[3*(i*width + j)+0],
                                    bytes[3*(i*width + j)+1],
                                    bytes[3*(i*width + j)+2]))

    return image

if __name__ == '__main__':

    if(sys.argv[0] == "-b"):
        #binary mode - bin -> png
        if(sys.argv[1] == 's'):
            fileName = sys.argv[2]
            image = read_image(fileName + ".bin")
            fileName += ".png"
            image.save(fileName)
        elif(sys.argv[1] == 'm'):
            for i in range(sys.argv[3]):
                fileName = sys.argv[1]
                image = read_image(fileName + i + ".bin")
                fileName += i
                fileName += ".png"
                image.save(fileName)
    else: 
        #image mode - png -> bin
        if(sys.argv[0] == 's'): #single file mode
            fileName = sys.argv[1]
            image = Image.open(fileName + ".png")
            fileName += ".bin"
            write_image(image, fileName)

        elif(sys.argv[0] == 'm'): #multiple file mode
            for i in range(sys.argv[2]):
                fileName = sys.argv[1]
                image = Image.open(fileName + i + ".png")
                fileName += i
                fileName += ".bin"
                write_image(image, fileName)
        else:
            print("ERROR: incorrect arguments passed")


