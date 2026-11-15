//  Project Title: Filter2D2013 (2D Filter)
#define _CRT_SECURE_NO_WARNINGS

#include < iostream >
#include < fstream >
#include < string >
#include < io.h >
#include < dos.h >
#include < conio.h >
#include < stdlib.h >
#include < sstream >
#include < stdio.h >
#include < iomanip >
#include < istream >
#include < math.h >

using namespace std;

class Filter2D2013 {

	int n1; // matrix size x
	int n2; // matrix size y

public:

	int getNofPixelsX(void) { return this->n1; };

	int getNofPixelsY(void) { return this->n2; };

	void setNofPixelsX(int x) { this->n1 = x; };

	void setNofPixelsY(int y) { this->n2 = y; };

public:

	struct data {

		double **fMRI; // pointer to the matrix entry 
		
		double **Filter2D; // pointer to the matrix entry

	}*pointer; // pointer to the matrices

public:

	Filter2D2013(int x, int y) : n1(x), n2(y) { pointer = 0; };// constructor 
	
	void allocateData();

	void save();

	~Filter2D2013() { } // destructor

};

void Filter2D2013::allocateData() { // allocate data


	 // (1) allocate struct 'data' (begin)
	 pointer = new data;
			
	 pointer->fMRI = new double*[this->n2];

	 pointer->Filter2D = new double*[this->n2]; 


	 for( int v=0; v < this->n2; v++ ) { // (1)
		 
		 pointer->fMRI[v] = new double[this->n1];

		 pointer->Filter2D[v] = new double[this->n1];

	  } // (1) allocate struct 'data' (end)


		// (2) initialize (begin)
		for( int v=0; v < this->n2; v++ ) { // (a)

			for( int f=0; f < this->n1 ; f++ ) { // (b)
		 
			pointer->fMRI[v][f] = (double)0.0;

			pointer->Filter2D[v][f] = (double)0.0;

			 } //(b)

		 } //(a)
		// (2) initialize (end)

} // allocate data


void Filter2D2013::save() { // saveImages

	FILE * savedata;
	char outputFile[128];
	
	sprintf(outputFile, "%s","Image.img");

	if ((savedata = fopen(outputFile,"wb+"))==NULL)
	{

		std::cout << "Cannot open output file, Now Exit..." << endl;

	} else  { // (save)


	for( int v=0; v < this->n2; v++ ) { // (a)

		for( int f=0; f < this->n1; f++ ) 
	
		fwrite(&pointer->fMRI[v][f],sizeof(double),1,savedata);

	} // (a)

	fclose(savedata);

	} // (save)

	
	sprintf(outputFile, "%s","Filter2D.img");
	if ((savedata = fopen(outputFile,"wb+"))==NULL)
	{

		std::cout << "Cannot open output file, Now Exit..." << endl;

	} else  { // (save)


	for( int v=0; v < this->n2; v++ ) { // (a)

		for( int f=0; f < this->n1; f++ ) 
	
		fwrite(&pointer->Filter2D[v][f],sizeof(double),1,savedata);

	} // (a)

	fclose(savedata);

	} // (save)

} // saveImages



int main ( int argc, char * argv[] ) {

	char outputFile[128]="Filter2D2017.log";

	FILE * savedata;

if (argc < 6) { std::cout << endl;
				 std::cout << "Please type the image file name" << endl;
				 std::cout << "Please make sure that the image format is Analyze 'double': 64 bits real" << endl;
				 std::cout << "Please enter the number of pixels along the X direction (integer)" << endl;
				 std::cout << "Please enter the number of pixels along the Y direction (integer)" << endl;
				 std::cout << "Please type 'l' to apply a low pass filter or 'h' to apply a high pass filter " << endl; 
				 std::cout << "Please enter the cut-off frequency (double in: [0.01, 0.99])" << endl;
				 std::cout << endl;
				 exit(0); }

else { // run the program (begin)

	
	if ((savedata = fopen(outputFile,"w"))==NULL)
	{

		std::cout << "Cannot open output file, Now Exit..." << endl;

	} else  { // processing (begin)

	int n1 = atoi(argv[2]);
	int n2 = atoi(argv[3]);

	char imageFileName[128];

	unsigned char filterType = 'l';

	filterType = *argv[4];

	sprintf(imageFileName, "%s", argv[1]);

	double m_cof = atof(argv[5]);

	if ( m_cof < (double) 0.01 || m_cof > (double) 0.99 )
	{
	
		std::cout << "The cut-off frequency should be a double number in the range: [0.01, 0.99]" << endl;
		exit(0);

	}

	std::cout << endl;
	std::cout << "The image file name is: " << imageFileName << endl;
	std::cout << "The number of pixels along the X direction is: " << atoi(argv[2]) << endl;
	std::cout << "The number of pixels along the Y direction is: " << atoi(argv[3]) << endl;

	if ( tolower(filterType) == 'l' )
	std::cout << "The program applies a low pass filter to the Image Data " << filterType << endl;
	else if ( tolower(filterType) == 'h' ) 
	std::cout << "The program applies a high pass filter to the Image Data " << filterType << endl;

	fprintf(savedata,"%s%s\n", "The image file name is: " , imageFileName);
	fprintf(savedata,"%s%d\n", "The number of pixels along the X direction is: ", n1);
	fprintf(savedata,"%s%d\n", "The number of pixels along the Y direction is: ", n2);

	if ( tolower(filterType) == 'l' )
	fprintf(savedata,"%s%c\n", "The program applies a low pass filter to the Image Data: ", filterType);
	else if ( tolower(filterType) == 'h' )
	fprintf(savedata,"%s%c\n", "The program applies a high pass filter to the Image Data: ", filterType);
	fprintf(savedata,"\n");

	Filter2D2013 Filter2D(n1,n2);

	Filter2D.allocateData();

	/// read image file (begin)
	FILE * pf;

	if ((pf = fopen(imageFileName,"rb+"))==NULL)
	{

		std::cout << "Cannot open file: " << imageFileName << endl;
		fprintf(savedata,"%s%s\n", "Cannot open file: " , imageFileName );
		exit(0);

	} else { // else

	double number;

	for (int i1=0; i1 < n2; i1++) {// x dim
       	
		for (int i2=0; i2 < n1; i2++) { // y dim
			
		fread(&number,sizeof(double),1,pf);
		
		Filter2D.pointer->fMRI[i1][i2] = (double)number;
                          
		} // y dim
        
	}  // x dim 

      	
    fclose (pf);


	} // else 
	/// read image file (end)

	
	std::cout << "Image data loaded" << endl;
	    
	int XNEI = (int)2;
    int n7 = ( (int)floor( (double)n2/2.0) );  
	int n8 = ( (int)floor( (double)n1/2.0) );

	// build the FILTER function www.wikipedia.org & www.dspguide.com/ch14/5.htm (begin)
	double pi = 3.141592;
	double alpha = 0.0, cutOFF_frequency = m_cof;

	    FILE * fir;
		char fir_filename[128] = "FrequencyResponse.txt";
		double Gain = 0.0;
		double fs = 0.0;

		fir = fopen(fir_filename, "w+");

		for (fs = (double)0.001; (double) fs <= (double) 1.0; fs += (double)0.0025)
		{ // build the FIR plot (begins) 
		/// at the end of the loop, filtered data
		/// will be saved: when fs (sampling frequency) = 1.0
		/// see (***)
			
		// fs is the sampling frequency 
		// deltaT is the sampling period

			Gain = (double)0.0;


	for (int pp =-n7+XNEI; pp < n7-XNEI; pp++) {

            for (int qq =-n8; qq < n8; qq++) {

                if ( tolower(filterType) == 'l' ) // if low pass filter 
				{

				// Step 1: Declare a variable named ' x ' and assign to it
				// the value of the 'i-th' pixel brightness (signal). 
				// Hint: 1. To access the signal ' fMRI ' use the pointer ' pointer '
				// after the use of the object ' Filter2D '.
				// 2. The i-th pixel brightness is by the index ' [pp + n7][qq + n8] '
                // 3. The i-th pixel brightness is the value termed ' xi ' in Wikipedia notes
				double x = Filter2D.pointer->fMRI[pp + n7][qq + n8];

				// Step 2: Declare a variable named ' y ' and assign to it
				// the value of the 'ith - 1' filtered signal.
				// Hint: 1. To access the filtered signal ' Filter2D ' use the pointer ' pointer '
				// after the use of the object ' Filter2D '.
				// 2. The 'i-th - 1' filtered signal is by the index ' [pp + n7 - 1][qq + n8] '
				// 3. The 'i-th - 1' filtered signal is the value termed ' yi ' in Wikipedia notes
				double y = Filter2D.pointer->Filter2D[pp + n7 - 1][qq + n8];

				// Step 3: Declare a variable named ' RC ' and assign to it the 
				// numerical value of the ' RC ' constant as per Wikipedia notes. 
				// Hint: The ' RC ' constant includes in its formulation the
				// cut-off frequency wich you may want to call as: ' cutOFF_frequency ' 
				double RC = (double) 1.0 / ((double) 2.0 * pi * cutOFF_frequency);

				// Step 4: Declare a variable named ' deltaT ' and assign to it
				// the inverse of the sampling frequency. Hint: The sampling 
				// frequency is the counter ' fs ' of the outer for loop that
				// builds the frequency response of the filter.
				double deltaT = ((double)1.0 / fs);

				// Step 5: Calculate the value of the smoothing factor: ' alpha '
				// Hint: 1. Use the formula as per Wikipedia notes. 2. Check with
				// an if else statement if the value of the denominator of ' alpha '
				// is equal to zero, and in such case assign the value ' 1.0 ' to
				// alpha. Use the formula given for the lowpass filter
				if ( ((double) RC + deltaT) != 0.0 )

					alpha = ((double) deltaT) / ((double) RC + deltaT);

				else alpha = (double) 1.0;

				// Step 6: Calculate the value of the ' ith ' filtered signal value
				// ' Filter2D ' which is by the index ' [pp + n7][qq + n8] '
				// Hint: Use Wikipedia notes to calculate the the ' ith ' filtered signal value.
				// To access the filtered signal ' Filter2D ' use the pointer ' pointer '
				// after the use of the object ' Filter2D '.
				Filter2D.pointer->Filter2D[pp + n7][qq + n8] = ((double) alpha * x ) + 
					                                          (((double)1.0-alpha) * y);
				}// if low pass  filter
				else if ( tolower(filterType) == 'h' ) // if high pass filter
				{

                // Step 1: Declare a variable named ' x ' and assign to it
				// the value of the 'i-th' pixel brightness (signal). 
				// Hint: 1. To access the signal ' fMRI ' use the pointer ' pointer '
				// after the use of the object ' Filter2D '.
				// 2. The i-th pixel brightness is by the index ' [pp + n7][qq + n8] '
                // 3. The i-th pixel brightness is the value termed ' xi ' in Wikipedia notes
				double x  = Filter2D.pointer->fMRI[pp + n7][qq + n8];
				
				// Step 2: Declare a variable named ' w ' and assign to it
				// the value of the 'i-th - 1' pixel brightness (signal). 
				// Hint: 1. To access the signal ' fMRI ' use the pointer ' pointer '
				// after the use of the object ' Filter2D '.
				// 2. The 'i-th - 1' pixel brightness is by the index ' [pp + n7 - 1][qq + n8] '
                // 3. The 'i-th - 1' pixel brightness is the value termed ' xi - 1 ' in Wikipedia notes
				double w = Filter2D.pointer->fMRI[pp + n7 - 1][qq + n8];

				// Step 3: Declare a variable named ' y ' and assign to it
				// the value of the 'ith - 1' filtered signal.
				// Hint: 1. To access the filtered signal ' Filter2D ' use the pointer ' pointer '
				// after the use of the object ' Filter2D '.
				// 2. The 'i-th - 1' filtered signal is by the index ' [pp + n7 - 1][qq + n8] '
				// 3. The 'i-th - 1' filtered signal is the value termed ' yi ' in Wikipedia notes
				double y = Filter2D.pointer->Filter2D[pp + n7 - 1][qq + n8];

				// Step 4: Declare a variable named ' RC ' and assign to it the 
				// numerical value of the ' RC ' constant as per Wikipedia notes. 
				// Hint: The ' RC ' constant includes in its formulation the
				// cut-off frequency wich you may want to call as: ' cutOFF_frequency ' 
				double RC = (double) 1.0 / ((double) 2.0 * pi * cutOFF_frequency);

				// Step 5: Declare a variable named ' deltaT ' and assign to it
				// the inverse of the sampling frequency. Hint: The sampling 
				// frequency is the counter ' fs ' of the outer for loop that
				// builds the frequency response of the filter.
				double deltaT = ((double)1.0 / fs);

				// Step 6: Calculate the value of the smoothing factor: ' alpha '
				// Hint: 1. Use the formula as per Wikipedia notes. 2. Check with
				// an if else statement if the value of the denominator of ' alpha '
				// is equal to zero, and in such case assign the value ' 1.0 ' to
				// alpha. 3. Note that this value is different versus the value you
				// calculate for the lowpass filter. See Wikipedia notes.
				if ( ((double) RC + deltaT) != 0.0 )

					alpha = ((double) RC) / ((double) RC + deltaT);

				else alpha = (double) 1.0;

				// Step 7: Calculate the value of the ' ith ' filtered signal value
				// ' Filter2D ' which is by the index ' [pp + n7][qq + n8] '
				// Hint: Use Wikipedia notes to calculate the the ' ith ' filtered signal value.
				// To access the filtered signal ' Filter2D ' use the pointer ' pointer '
				// after the use of the object ' Filter2D '.
				Filter2D.pointer->Filter2D[pp + n7][qq + n8] = ((double) alpha * y ) + 
					                                          (((double)alpha) * ((double)x - w ));
				
				}// if high pass filter
                 
				// calculate Gain (begins)
				if ( (double) Filter2D.pointer->fMRI[pp + n7][qq + n8] != (double) 0.0 )
				{

					double ratio =  ((double) Filter2D.pointer->Filter2D[pp + n7][qq + n8]) / 
						            ((double) Filter2D.pointer->fMRI[pp + n7][qq + n8] );

					if ( ratio > 0.0 )
					{
						Gain += (double) 10.0 * log10 ( (double) ratio );

					}
					else Gain += (double) 0.0;


				if ( (_isnan((double)Gain)) == 0 ) { }

					else { Gain += (double) 0.0; }

				} else { Gain += (double) 0.0; }
				// calculate Gain (ends)

			}
        } // build the FILTER function www.wikipedia.org & www.dspguide.com/ch14/5.htm (end)

		// save the FR text data
		fprintf_s(fir, "%lf\t \t %lf\n", (double)fs/m_cof, (double)Gain); // fr

		} // build the FR plot (ends)

		fclose(fir); // fir

		fprintf(savedata,"%s\n", "Now Saving Filtered Data");
    
		            char filename[128];
					// saving filtered data obtained with the value of fs = 1.0
					// sampling frequency = 1.0 
					// see (***)
					sprintf(filename, "%s%s", "Filtered-", imageFileName);

					fprintf(savedata, "%s\t%s\n", "Now Saving Filtered Data in File: ", filename);

						if ((pf = fopen(filename,"wb+"))==NULL)
						{

							fprintf(savedata, "%s\n", "Cannot open file to save Bessel Filtered Data");

							delete Filter2D.pointer;
							Filter2D.~Filter2D2013();

							exit(0);
	
						} else { // save data


						for (int i1=0; i1 < n2; i1++) {// x dim
       	
								for (int i2=0; i2 < n1; i2++) { // y dim

								double savedata2 = (double)Filter2D.pointer->Filter2D[i1][i2];
          
								fwrite(&savedata2,sizeof(double),1,pf);

							}
						} ///save FilteredSignal data

						fprintf(savedata,"%s\n", "Filtered Data Saved");

						fclose (pf);

						fclose(savedata);
						system(outputFile);
	
						} // save data

	std::cout << "Filter calculated" << endl;

	Filter2D.save();

	std::cout << "End of Computation..." << endl;

	fprintf(savedata,"%s\n", "End of Computation...");
	fprintf(savedata,"\n");

	fclose(savedata);
	delete Filter2D.pointer;
	Filter2D.~Filter2D2013();
	} // processing (end)

	} // run the program (end)
	
	return 0;
} // end of main