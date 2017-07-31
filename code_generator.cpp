#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

int cell_size = 50;

void print_array(unsigned char * array){
	for (int i = 0; i < 5; i++){
		std::cout << (int)array[i];
	}
	std::cout << std::endl;
}

void draw_image(cv::Mat mat, unsigned char *array, int i){
	for (int j = 0; j < 5; j++){
		cv::Mat roi = mat(cv::Rect((j+1)*cell_size,((i/2)+1)*cell_size,cell_size,cell_size));
		if (array[j]){
			roi.setTo(cv::Scalar(255));
		}
	}
}

int main(int argc, char **argv){
	if (argc < 2){
		std::cout << "usage: " << argv[0] << " ID1 [ID2, ID3..] path_to_save_images" << std::endl;
		return 1;
	}
	for (int k = 1; k < argc - 1; k++){
		unsigned char* hamming_code = new unsigned char[5];
		int number = atoi(argv[k]);
		cv::Mat img = cv::Mat::zeros(7*cell_size, 7*cell_size, CV_8UC1);
		for (int i = 0; i < 10; i+=2){
			int val = ((number << i)&0x200)>>9;
			hamming_code[2] = val;
			val = ((number << (i+1))&0x200)>>9;
			hamming_code[4] = val;
			// bit 0
			hamming_code[0] = (hamming_code[2] && hamming_code[4])?0:1;
			// bit 1
			hamming_code[1] = (hamming_code[2])?1:0;
			// bit 3
			hamming_code[3] = (hamming_code[4])?1:0;
			draw_image(img, hamming_code, i);
			
		}
		char result[512];

		strcpy(result,argv[argc-1]);
		strcat(result,"ar_code_");
		strcat(result,argv[k]);
		strcat(result,".png");
		std::string name (result);
		std::cout << name << std::endl;
		cv::imshow(name, img);
		cv::imwrite(name, img);
	}
	cv::waitKey(0);
	return 0;
}