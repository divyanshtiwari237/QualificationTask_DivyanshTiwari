#include "pbPlots.hpp"
#include "supportLib.hpp"
#include<vector>

static void simplePlotter(std::vector<double> y1, std::vector<double> t1,std::vector<double> y2, std::vector<double> t2,std::string s)
{
    bool success;
    StringReference *errorMessage = new StringReference();
	RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();
   ScatterPlotSeries *series1 = GetDefaultScatterPlotSeriesSettings();
	series1->xs = &t1;
	series1->ys = &y1;
	series1->linearInterpolation = true;
	series1->lineType = toVector(L"solid");
	series1->lineThickness = 2;
    series1->pointType =toVector(L"triangles");
	series1->color = CreateRGBColor(1,0,0);

    ScatterPlotSeries *series2 = GetDefaultScatterPlotSeriesSettings();
	series2->xs = &t2;
	series2->ys = &y2;
	series2->linearInterpolation = true;
	series2->lineType = toVector(L"solid");
    series2->pointType =toVector(L"circles");
	series2->lineThickness = 2;
	series2->color = GetBlack();

	ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
	settings->width = 600;
	settings->height = 400;
	settings->autoBoundaries = true;
	settings->autoPadding = true;
	settings->title = toVector(L"x-y");
	settings->xLabel = toVector(L"x axis");
	settings->yLabel = toVector(L"Y axis");
	settings->scatterPlotSeries->push_back(series1);
    settings->scatterPlotSeries->push_back(series2);

	success = DrawScatterPlotFromSettings(imageReference, settings, errorMessage);

    if(success)
    {
        std::vector<double> *pngdata = ConvertToPNG(imageReference->image);
        WriteToFile(pngdata, s);
        DeleteImage(imageReference->image);
	}
    else
    {
	    std::cerr << "Error: ";
        for(int i = 0; i < errorMessage->string->size(); i++){
           std:: wcerr << errorMessage->string->at(i);
    }
        std::cerr <<std:: endl;
	}

    


}