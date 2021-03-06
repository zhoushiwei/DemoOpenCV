#ifndef _FTS_LV_REDSIGNALVIOLATION_
#define _FTS_LV_REDSIGNALVIOLATION_


#include "FTSVideoAlgorithm.h"
#include "CVLight.h"
#include "CVLine.h"

//#define MEASURE_TIME_REDLIGHT
//#define TUNNING_RED_LIGHT
class FTSRedSignalViolation:
	public FTSVideoAlgorithm {

protected:
	enum DETECTION_MODE{ MOVING_DIRECTION = 0, CROSSING_DOUBLE_LINES, CROSSING_SINGLE_LINES};
	std::string strRoiImg;
	std::string strStopRoiImage;
	float fScaleRatio;
	float fVarThreshold;
	float fMaxLearningRate;

	// Traffic light
	Light lightRed, lightGreen, lightYellow;
	cv::Rect rectTrafficLight;
	Line_<double> inLine, outLine;

	int iHistory;
	int iTrainingFrame;
	int iInterval;
	int iContourMinArea;
	int iContourMaxArea;
	// 1  Prefer direction
	// 2  Double-line
	DETECTION_MODE detectionMode;

	bool bHardThreshold;
	
	//tracker params
	float _dt;
	float _Accel_noise_mag;
	double _dist_thres;
	double _cos_thres;
	int _maximum_allowed_skipped_frames;
	int _max_trace_length;
	double _very_large_cost;

	CascadeClassifier cascade;
public:
	static std::string const className() { return "FTSRedSignalViolation"; }
	virtual cv::AlgorithmInfo* info() const;
	virtual void read(const FileNode& fn);
	virtual void write(FileStorage& fs) const;
	virtual void operator() (FTSCamera camInfo);


	FTSRedSignalViolation();
	~FTSRedSignalViolation();
	void transformLightIntoNewAxis(Light& light, cv::Point transformMat);
	bool checkRedSignal(bool isRed, const cv::Mat& redTL, Light& red_light, const cv::Mat& yelTL, Light& yel_light, const cv::Mat& grnTL, Light& grn_light);
};

#endif