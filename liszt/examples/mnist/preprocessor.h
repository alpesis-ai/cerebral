#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

int preprocess()
{
    // convert the image vector to image matrix (28 * 28)
    char number;
    for (int j = 1; j <= height; ++j)
    {
        for (int i = 1; i <= width; ++i)
        {
            image.read(&number, sizeof(char));
            if (number == 0)
            {
                digit[i][j] = 0;
            } else
            {
                digit[i][j] = 1;
            }
        }
    }

    /*
    // print the digit image
    cout << "Image: " << endl;
    for (int j = 1; j <= height; ++j)
    {
        for (int i = 1; i <= width; ++i)
        {
            cout << digit[i][j];
        }
        cout << endl;
    }
    */


    // convert the digit to the out1
    for (int j = 1; j <= height; ++j)
    {
        for (int i = 1; i <= width; ++i)
        {
            int pos = i + (j - 1) * width;
            out1[pos] = digit[i][j];
        }
    }

    // read the label
    label.read(&number, sizeof(char));
    for (int i = 1; i <= n3; ++i)
    {
        expected[i] = 0.0;
    }
    expected[number+1] = 1.0;
    cout << "Label: " << (int)(number) << endl;

    return (int)(number);
}

#endif
