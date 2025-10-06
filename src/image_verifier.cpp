#include "image_verifier.h"
#include "user.h"
#include <opencv2/opencv.hpp>
#include <fstream>
#include <iostream>

using namespace cv;
using namespace std;

double ImageVerifier::compareWithUserImage(const string& username, const string& userImgPath) {
    UserManager um(dbPath);
    vector<unsigned char> imgData = um.getUserImage(username);
    if (imgData.empty()) {
        cerr << "No reference image for user " << username << endl;
        return 0.0;
    }

    // decode stored reference image
    Mat ref = imdecode(imgData, IMREAD_COLOR);
    Mat user = imread(userImgPath, IMREAD_COLOR);
    if (ref.empty() || user.empty()) {
        cerr << "Error loading images.\n";
        return 0.0;
    }

    resize(user, user, ref.size());
    Mat diff;
    absdiff(ref, user, diff);
    diff = diff.mul(diff);
    Scalar s = sum(diff);
    double sse = s.val[0] + s.val[1] + s.val[2];
    if (sse <= 1e-10) return 100.0;
    double mse = sse / (double)(ref.channels() * ref.total());
    double psnr = 10.0 * log10((255 * 255) / mse);
    return min(100.0, psnr); // clamp to 100
}
