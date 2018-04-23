videoer = [
'https://www.youtube.com/watch?v=dQw4w9WgXcQ',
'https://www.youtube.com/watch?v=cpPG0bKHYKc',
'https://www.youtube.com/watch?v=hFhiV5X5QM4',
'https://www.youtube.com/watch?v=6r1DFGpBzrc',
'https://www.youtube.com/watch?v=Ow3CcOGNIss',
'https://www.youtube.com/watch?v=z9Uz1icjwrM']

def forkort():
    for i in range(len(videoer)):
        link = videoer[i]
        ny_link = "youtu.be/" + link[32:len(link)]
        print(ny_link)

forkort()
