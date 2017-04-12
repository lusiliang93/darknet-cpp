#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

void parse()
{

}
int main(int argc, char* argv[])
{
    char* str = argv[1];
	VideoCapture cap(str);

	if(!cap.isOpened())
		return -1;
	Mat src;
    cap >> src;

    //--- INITIALIZE VIDEOWRITER
    VideoWriter writer;
    int codec = CV_FOURCC('M', 'J', 'P', 'G');  // select desired codec (must be available at runtime)
    double fps = 25.0;                          // framerate of the created video stream
    string filename = "./seat.avi";             // name of the output video file according to input name //change!!
    writer.open(filename, codec, fps, src.size(), true);
    // check if we succeeded
    if (!writer.isOpened()) {
        cerr << "Could not open the output video file for write\n";
        return -1;
    }

    //--- GRAB AND WRITE LOOP
    cout << "Writing videofile: " << filename << endl
         << "Press any key to terminate" << endl;
    int i=0;
    for(;;){
        // check if we succeeded
        cap >> src;
        if (src.empty()) {
             break;
         }
        // encode the frame into the videofile strea
        if(i % 2 == 0)
            writer << src;
        i++;
        printf("count:%d\n",i);
        // show live and wait for a key with timeout long enough to show images
        imshow("Live", src);
        if (waitKey(5) >= 0)
            break;

    }

	writer.release();
	cout << "Finished writing" << endl;
	return 0;
}
