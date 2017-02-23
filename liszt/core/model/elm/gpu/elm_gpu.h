#ifndef ELMGPU_H
#define ELMGPU_H


class ELMGPU
{
    public:
        ELMGPU();
        ~ELMGPU();

        vector<vector<float>> readCSV(string fileName, bool header, float& time);
        double writeCSV(vector<vector<float>> data, string fileName);

};

#endif
