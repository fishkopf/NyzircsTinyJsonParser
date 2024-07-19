#include <string>
#include "JsonParser.h"
#include<iostream>

int main()
{
	std::string jsonStr = "{'conv':{'tensor':{'mat':[1,2,3,4,5],'height':'5','widht':'5',},'bias':9},'mp':{},'conv2':{'tensor':{'mat':[0.123,0.456,0.8,1934,32434.5234],'height':'9','widht':'4',},'bias':'2'},'mp2':{},'FC':{'weights':{'mat':[9,7,4,2],'height':'9','widht':'4'}}}";
    CJsonParser node;
    node.parse(jsonStr);
	
}