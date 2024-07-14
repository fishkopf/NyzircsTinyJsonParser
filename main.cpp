#include <string>
#include "JsonParser.h"
#include<iostream>

int main()
{
	std::string jsonStr = "{'conv':{'tensor':{'mat':[1,2,3,4,5],'height':'5','widht':'5',},'bias':1},'mp':{},'conv2':{'tensor':{'mat':[6,7,8,9,0],'height':'9','widht':'4',},'bias':'1'},'mp2':{},'FC':{'weights':{'mat':[9,7,4,2],'height':'9','widht':'4'}}}";
    CJsonParser node;
    node.parse(jsonStr);
	
}