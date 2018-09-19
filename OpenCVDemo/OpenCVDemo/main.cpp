//
//  main.cpp
//  OpenCVDemo
//
//  Created by soson on 2018/9/18.
//  Copyright © 2018年 soson. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    //读取图片
//    Mat img = imread("/Users/soson/Desktop/OpenCVDemo/OpenCVDemo/girl.jpeg");
//    imshow("image",img);
//    waitKey(0);
    
    
//    创建mat矩阵
//    构造2行3列float类型的单通道矩阵
    Mat m = Mat(2,3,CV_32FC(1));
    Mat mSize = Mat(Size(3,2),CV_32FC(1)); //Size方式，与上面同等
    
    Mat mC;
    mC.create(2,3,CV_32FC1);
    mC.create(Size(3,2),CV_32FC1);
    
//    OpenCV 的 Size类，该类一般用来存储矩阵的列数和行数。 需要注意的是 ， Size的第一个元素是矩阵的列数(宽)，第二个元素是矩阵的行数(高)， 即先存宽，再存高
//    常见的0矩阵和1矩阵构造方法
    Mat mO = Mat::ones(2,3,CV_32FC1);
    Mat mOS = Mat::ones(Size(3,2),CV_32FC1);
    
    Mat mZ = Mat::zeros(2,3,CV_32FC1);
    Mat mZS = Mat::zeros(Size(3,2),CV_32FC1);
    
    
//    使用成员变量rows和cols获取矩阵的行数和列数
    cout <<"m.rows"<<m.rows<<",m.cols"<<m.cols<<endl;
    
//    使用成员函数size()获取矩阵的尺寸
    cout <<"m.size:"<<m.size<<endl;
    
    
//    使用成员函数channels()获取矩阵的通道数
    cout <<"m.channels():"<<m.channels()<<endl;
    
//    成员函数total()返回矩阵的行数乘以列数，即是面积
    cout <<"m.total():"<<m.total()<<endl;
    
//    成员变量dims表示矩阵的维数
    cout <<"m.dims:"<<m.dims<<endl;
    
    cout<< "------------------------------" <<endl;
    
//    访问单通道Mat对象中的值
//    成员函数at
    for (int r = 0;r<m.rows; r ++){
        for(int c = 0;c<m.cols; c ++){
            cout<<m.at<int>(r,c)<<endl;
        }
    }
    
    cout<< "------------------------------" <<endl;

//    成员函数ptr
    for (int r =0; r < m.rows; r ++)
    {
        //得到矩阵m的第r行行首的地址
        const int * ptr = m.ptr<int>(r);
        for(int c = 0; c < m.cols; c++)
        {
            //打印第r行的所有值
            cout << ptr[c] <<endl;
        }
    }
    
    
    cout<< "------------------------------" <<endl;
    
//    成员函数isContinuous()
//    isContinuous返回值如果为true，表示所有的值都是连续存储的。
    
    //少使用一个for循环
    if(m.isContinuous())
    {
        //得到矩阵m的第一个值的地址
        int *ptr = m.ptr<int>(0);
        //利用操作符“[]”取值
        for(int n = 0;n<m.rows*m.cols;n++)
        {
            cout<< ptr[n] <<endl;
        }
    }
    
    cout<< "------------------------------" <<endl;
    
    
//    构造多通道Mat对象
//    构造一个2行2列的float类型的三通道矩阵
    Mat mm = (Mat_<Vec3f>(2,2)<<Vec3f(1,2,3),Vec3f(4,5,6),Vec3f(7,8,9),Vec3f(10,11,12));
    
    
//    访问多通道Mat对象中的值
//    多通道at函数
    for (int r = 0;r<mm.rows; r ++)
    {
        for(int c = 0;c<mm.cols; c ++){
            cout<<mm.at<Vec3f>(r,c)<<endl;
        }
    }
    
    cout<< "------------------------------" <<endl;
    
//    多通道ptr函数
    for (int r =0; r < mm.rows; r ++)
    {
        //得到矩阵mm每行首元素的地址
        Vec3f * ptr = mm.ptr<Vec3f>(r);
        
        for(int c = 0; c < mm.cols; c++)
        {
            //打印第r行的所有值
            cout << ptr[c] <<endl;
        }
    }
    
    
    cout<< "------------------------------" <<endl;
    
    
//    多通道isContinuous()函数
    if(mm.isContinuous())
    {
        //得到矩阵m的第一个值的地址
        Vec3f * ptr = mm.ptr<Vec3f>(0);
        //利用操作符“[]”取值
        for(int n = 0;n<mm.rows*mm.cols;n++)
        {
            cout<< ptr[n] <<endl;
        }
    }
    
    
    cout<< "------------------------------" <<endl;
    
//    多通道成员变量step和data
    for (int r =0; r < mm.rows; r ++)
    {
        for(int c = 0; c < mm.cols; c++)
        {
            //得到指向每个元素的指针
            Vec3f * ptr = (Vec3f*)(mm.data + r*mm.step[0] + c*mm.step[1]);
            cout << *ptr<<endl;
        }
    }
    
    cout<< "------------------------------" <<endl;
    
//    分离通道
//    使用OpenCV提供的split函数可分离多通道
    vector<Mat> planes;
    split(mm,planes);
    
    //输出三个通道的值
    for (int r =0; r < planes.size(); r ++)
    {
        cout << planes[r]<<endl;
    }
    
    cout<< "------------------------------" <<endl;
    
    
//    合并通道
//    使用OpenCV提供的merge函数可以将多个单通道矩阵合并为一个三维矩阵
//    单通道矩阵
    Mat plane0 = (Mat_<int>(2,2)<<1,2,3,4);
    Mat plane1 = (Mat_<int>(2,2)<<5,6,7,8);
    Mat plane2 = (Mat_<int>(2,2)<<9,10,11,12);
    
    //用三个单通道矩阵初始化为一个数组
    Mat plane[] = {plane0,plane1,plane2};
    
    Mat mat;
    merge(plane,3,mat);
    
    //合并的另一种写法
    //跟上面的实现一样一样
//    Vector<Mat> plane;
//    plane.push_back(plane0);
//    plane.push_back(plane1);
//    plane.push_back(plane2);
//    Mat mat;
//    merge(plane,mat);
    
    
//    获取Mat中某一区域的值,一般使用Rect类操作
//    Mat r= mm.rowRange(Range(1,2));  //获取矩阵第2，3行，索引从0开始。
//    Mat r1= mm.colRange(Range(0,1));  //获取矩阵第1，3列，索引从0开始。
    
    
//    使用成员函数clone和copyTo
//    clone和copyTo用于将矩阵克隆或者复制一份
//    Mat r_range= mm.rowRange(1,2).clone();
    
//    copyTo用法2
//    Mat r_range1;
//    mm.rowRange(1,2).copyTo(r_range1);
    
    
    
    
//    使用Rect类
//    Mat roi1 = mm(Rect(Point(2,1),Point(3,2))); //左上角的坐标，右下角的坐标
//    Mat roi2 = mm(Rect(2,1,2,2));                //x,y,宽度，高度
//    Mat roi3 = mm(Rect(Point(2,1),Size(2,2)));   //左上角的坐标，尺寸
    
                  
//    矩阵的运算（如果使用+号两个Mat的数据类型必须相同，如果使用add方法可以不同数据类型）
    Mat src1= (Mat_<uchar>(2,3)<<23,123,90,100,250,0);
    Mat src2= (Mat_<uchar>(2,3)<<125,150,60,100,10,40);
    Mat dst = src1 + src2;
    cout<< dst<<endl;
//    输出dst：
//    148，255，150
//    200，255，40
    
//    观察到123+150应该等于273，因为uchar类型的范围是255，超出了所以输出255.
    
    
    cout<< "------------------------------" <<endl;
    float value = 100;
    Mat dst1 = src1 + 100;
    cout<< dst1<<endl;
    
    
    cout<< "------------------------------" <<endl;
//    add函数
    Mat src3= (Mat_<uchar>(2,3)<<23,123,90,100,250,0);
    Mat src4= (Mat_<float>(2,3)<<125,150,60,100,10,40);
    Mat dst2;
    add(src3,src4,dst2,Mat(),CV_64FC1);
    cout<< dst2<<endl;
    
//    减法
    Mat dst3 = src1 - src2;
    cout<< dst3<<endl;
//    出现负数会取值为0
    
    
//    乘法
//    Mat的成员函数mul(),两个Mat对象的数据类型必须相同才能进行点乘
    Mat dst4 = src1.mul(src2);
    
//    Mat的乘法，还可以使用gemm函数
//    multiply函数
//    不局限于src1和src2的数据类型必须相同，在点乘结果的基础上还可以再乘以系数scale。
//    multiply(src1,scr2,dst,1.0,CV_32FC1);
    
    
//    除法
    Mat dst5 = src1 / src2;
//    两个Mat对象的数据类型必须相同才能进行点除
//    Mat的成员函数divide(),不局限于src1和src2的数据类型必须相同
    
    
    
    
//    将灰度图转换为Mat
//    1.CV_LOAD_IMAGE_COLOR:彩色图像
//    2.CV_LOAD_IMAGE_GRAYSCALE:灰度图像
//    3.CV_LOAD_IMAGE_ANYCOLOR：任意图像
//    Mat img = imread("/Users/soson/Desktop/OpenCVDemo/OpenCVDemo/girl.jpeg",CV_LOAD_IMAGE_GRAYSCALE);
//    imshow("image",img);
//    waitKey(0);
    
    
//    将彩色图转为Mat
//    imread读取彩色图片,读取后的格式是BGR
    Mat img = imread("/Users/soson/Desktop/OpenCVDemo/OpenCVDemo/girl.jpeg");
    imshow("image",img);
    cout<< img.channels() <<endl;
    
    vector<Mat> planes1;
    split(img, planes1);
    //显示B通道
    imshow("B",planes1[0]);
    //显示G通道
    imshow("G",planes1[1]);
    //显示R通道
    imshow("R",planes1[2]);
     waitKey(0);
    
    return 0;
}
