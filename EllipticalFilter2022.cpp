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

const double ft_SCALE_z = 1.0;
const double ft_SCALE = 1.0;
unsigned char filterType = 'l';

void OnZTransform_scale(char imageFilename[], int rcxres, int rcyres, double m_Real, double m_Imaginary);
void OnZTransform(char imageFilename[], int rcxres, int rcyres, double m_Real, double m_Imaginary);
void OnTransferFunction(int rcxres, int rcyres, int n_poles, double m_cof, double m_eps, double m_Real, double m_Imaginary, int ax, int by);
void OnInverseZTransformTransferFunction(char filename[], int rcyres, int rcxres, double m_Real, double m_Imaginary);
void OnFourierTransform(char imageFilename[], int rcxres, int rcyres);


// declare a class by the name 'ZTransform2019'
class ZTransform2019 {

	// the point is to assign to 'n1' and 'n2' 
	// the correct values from the command console
	int n1; // matrix size x (number of pixels along the x direction)
	int n2; // matrix size y (number of pixels along the y direction)

// declare the class methods
// and embed the methods body
// in the class specification
public:

	// declare a method that returns the number
	// of pixels of the image along the x direction
	int getNofPixelsX(void) { return this->n1; };

	// declare a method that returns the number
	// of pixels of the image along the y direction
	int getNofPixelsY(void) { return this->n2; };

	// declare a method that sets the number
	// of pixels of the image along the x direction
	void setNofPixelsX(int x) { this->n1 = x; };

	// declare a method that sets the number 
	// of pixels of the image along the y direction
	void setNofPixelsY(int y) { this->n2 = y; };

public:
	// declare a structure ' data ' that defines the
	// pointers to pointers to the image
	struct data {

		double **Signal; // declare the pointer to pointer to the matrix (image) 


		}*pointer; // pointer to the element of the structure 'data'
	               // the pointer points to the memory address of the
	               // pointers to pointers 

public:

	// constructor of the class 'ZTransform2019'
	ZTransform2019(int x, int y) : n1(x), n2(y) { pointer = 0; }; 
		
	// declare the prototype of the 
	// function 'allocateData'
	// the function belongs to the 
	// sets of methods of the class 'ZTransform2019'
	void allocateData();

	// declare the prototype of the 
	// function 'save'
	// the function belongs to the 
	// sets of methods of the class 'ZTransform2019'
	void save();

	// destructor of the class 'ZTransform2019'
	~ZTransform2019() { } 

};

void ZTransform2019::allocateData() { // allocate data


	// (1) allocate struct 'data' (begin)
	// define a pointer by the name 'pointer'
	// and assign to it the instance of the
	// structure 'data' (the instance is a
	// memory address
	 pointer = new data;
	
	 // assign to the pointer to a pointer 'Signal' (pointer->Signal)
	 // the instance of the memory address of the pointer to pointer
	 // *[this->n2]. Practically define the memory address of the 
	 // rows of the matrix containing the image 'Signal'.
	 pointer->Signal = new double*[this->n2];

	 
	 for( int v=0; v < this->n2; v++ ) { // (1)
	 // at each iteration of the for loop
	 // assign to the pointer 'Signal[v]' the instance 
	 // of the memory address of the pointer [this-n1].
	 // Practically define the memory address of the 
	 // columns of the matrices containing the image:
	 // 'Signal.

		 pointer->Signal[v] = new double[this->n1];
		

		  } // (1) allocate struct 'data' (end)


		// (2) initialize (begin)
		for(int v=0; v < this->n2; v++ ) { // (a)

			for( int f=0; f < this->n1 ; f++ ) { // (b)
			
			// at each iteration of the two for loops
			// initializes the value of the pixel of
			// the image to zero. This is done for the
			// image 'Signal'.
			pointer->Signal[v][f] = (double)0.0;


			} //(b)

		 } //(a)
		// (2) initialize (end)

} // allocate data


void ZTransform2019::save() { // saveImages

	// declare a pointer to file
	// to be used to read the image
	FILE * savedata;
	// declare a string which contains
	// the file name of the image
	char outputFile[128];
	
	// assign the name string "Signal.img"
	// to the string 'outputFile'
	sprintf(outputFile, "%s","Signal.img");

	// open the image file in write-binary mode
	if ((savedata = fopen(outputFile,"wb"))==NULL)
	{
		// alert the user of possible failure in opening the file
		std::cout << "Cannot open output file, Now Exit..." << endl;
		exit(0);

	} else  { // (save)


	for( int v=0; v < this->n2; v++ ) { // (a)

		for( int f=0; f < this->n1; f++ ) 
	
		// at each iteration of the for loop saves the pixel
		// value contained at the memory address: ' &pointer->Signal[v][f] '
		fwrite(&pointer->Signal[v][f],sizeof(double),1,savedata);

	} // (a)

	// close the file afer saving
	fclose(savedata);

	} // (save)

	} // saveImages

int main ( int argc, char * argv[] ) {

	char outputFile[128]="Chebyshev2018.log";

if (argc < 11) { std::cout << endl;
				 std::cout << "Please type the image file name" << endl;
				 std::cout << "Please make sure that the image format is Analyze 'double': 64 bits real" << endl;
				 std::cout << "Please enter the following values: " << endl;
				 std::cout << "The number of pixels along the X direction (integer)" << endl;
				 std::cout << "The number of pixels along the Y direction (integer)" << endl;
				 std::cout << "Enter 'l' to calculate LPF or 'h' to calculate HPF" << endl;
				 std::cout << "The cut-off frequency as double precision number: 2.55 or 2.65" << endl;
				 std::cout << "The value of the real part of the complex number, (double) in: [0.01, 1]" << endl;
				 std::cout << "The value of the imaginary part of the complex number, (double) in: [0, 1]" << endl;				 
				 std::cout << "The number of poles of the filter, (int): 6, or 8" << endl;
				 std::cout << "The value of width of the ellipse: (int): 2, 4, 8, or 16" << endl;
				 std::cout << "The value of height of the ellipse: (int): 2, 4, 8, or 16" << endl;
				 std::cout << "The value of width and height of the ellipse are inversely proportional" << endl;
				 std::cout << "to the strength of the filter" << endl;
				 std::cout << "Suggested parameters for LPF: l 2.55 0.5 0.5 8 2 4" << endl;
				 std::cout << "Suggested parameters for HPF: h 2.55 0.5 0.5 8 16 4" << endl;
				 std::cout << endl;
				 exit(0); }

else { // run the program (begin)

	char imageFileName[128];
	sprintf(imageFileName, "%s", argv[1]);

	int n1 = atoi(argv[2]);
	int n2 = atoi(argv[3]);

	int m_rcxres = (int)n1;
	int m_rcyres = (int)n2;

	filterType = *argv[4];

	if ( tolower(filterType) != 'l' && tolower(filterType) != 'h' )
	{
	
		std::cout << "Enter 'l' to calculate LPF or 'h' to calculate HPF" << endl;
		exit(0);
	}

	double m_cof = atof(argv[5]);

	
	if ( m_cof != (double) 2.55 && m_cof != (double) 2.65 )
	{
	
		std::cout << "To use the filter please enter" << endl;
		std::cout << "the cut-off frequency as double precision number: 2.55 or 2.65" << endl;
		exit(0);

	}
	
	// reads from the command console the
	// value of the complex number
	double m_Real = atof(argv[6]);
	double m_Imaginary = atof(argv[7]);	

	if ( m_Real < (double) 0.01 || m_Real > (double) 1.0 )
	{
	
		std::cout << "To use the filter please enter" << endl;
		std::cout << "the real part of the complex number, (double) in: [0.01, 1]" << endl;
		std::cout << "The suggested value is 0.5" << endl;
		exit(0);

	}

	if ( m_Imaginary < (double) 0.0 || m_Imaginary > (double) 1.0 )
	{
	
		std::cout << "To use the filter please enter" << endl;
		std::cout << "the imaginary part of the complex number, (double) in: [0, 1]" << endl;
		std::cout << "The suggested value is 0.5" << endl;
		exit(0);

	}

	int n_poles = atoi(argv[8]);

	if ( n_poles != (int) 6 && n_poles != (int) 8 )
	{
	
		std::cout << "To use the filter please enter" << endl;
		std::cout << "the number of poles as an integer: 6, or 8" << endl;
		exit(0);

	}

	double m_eps = (double)0.05; // empirically tested	

	int by = atoi(argv[9]);
	int ax = atoi(argv[10]);

	if ( (int)ax != 2 && (int)ax != 4 && (int)ax != 8 && (int)ax != 16 )
	{

		std::cout << "Please reset the width of the ellipse to: 2, 4, 8, or 16" << endl;
	    exit(0);	

	}

	if ( (int)by != 2 && (int) by != 4 && (int)by != 8 && (int) by != 16 )
	{

		std::cout << "Please reset the width of the ellipse to: 2, 4, 8, or 16" << endl;
	    exit(0);	

	}

	if ( (int)ax == (int)by )
	{

		std::cout << "Please reset width and the height of the ellipse" << endl; 
		std::cout << "The two values must be different: 2, 4, 8, or 16" << endl;
	    exit(0);

	}

	if ( ((int)n_poles == 6 && (double)m_cof == 2.65 && (int)by == 4 && (int)ax == 16) || 
		 ((int)n_poles == 6 && (double)m_cof == 2.55 && (int)by == 4 && (int)ax == 16) || 
		 ((int)n_poles == 6 && (double)m_cof == 2.55 && (int)by == 16 && (int)ax == 4) ||
		 ((int)n_poles == 6 && (double)m_cof == 2.65 && (int)by == 16 && (int)ax == 4)
	   )
	{
		std::cout << "Please reset the number of poles to 8" << endl;
		exit(0);
	}

	char DataType[128];
	sprintf(DataType, "%s", "DOUBLE");
	FILE * savedata;
	char outputFile[128]="DATA.log";
	

	if ((savedata = fopen(outputFile,"w"))==NULL)
	{

		printf("Cannot open output file, Now Exit...");

	} else  { // processing (begin)

	double pi = 3.141592;
	double Zphase = (double)2.0*pi*atan2( (double)m_Imaginary, (double)m_Real ) / ((double)n1*n2);
	double magnitude = (double) sqrt ( (double)m_Real*m_Real + (double)m_Imaginary*m_Imaginary );

	printf("\n");
	printf("The image file name is: %s \n", imageFileName);
	printf("The DataType is: %s \n" , DataType);
	printf("The number of pixels along the X direction is: %d \n" , n1);
	printf("The number of pixels along the Y direction is: %d \n" , n2);
	std::cout << "The value of m_Real is: " << m_Real << endl;
	std::cout << "The value of m_Imaginary is: " << m_Imaginary << endl;
	std::cout << "The number of poles of the Chebyshev filter is: " << n_poles << endl; 
	printf("The width of the ellipse is: %d \n" , by);
	printf("The height of the ellipse is: %d \n" , ax);
	std::cout << "The magnitude of the Complex number is: " << magnitude << endl;
    std::cout << "The phase of the Complex number is: " << Zphase << endl;
	std::cout << "The cut-off frequency is: " << m_cof << endl;

	fprintf(savedata,"%s%s\n", "The image file name is: \n" , imageFileName);
	fprintf(savedata,"%s%s\n", "The DataType is: \n" , DataType);
	fprintf(savedata,"%s%d\n", "The number of pixels along the X direction is: \n", n1);
	fprintf(savedata,"%s%d\n", "The number of pixels along the Y direction is: \n", n2);
	fprintf(savedata,"%s%lf\n", "The cut-off frequency is: ", m_cof);
	fprintf(savedata,"%s%lf\n", "The value of m_Real is: ", m_Real);
	fprintf(savedata,"%s%lf\n", "The value of m_Imaginary is: ", m_Imaginary);
	fprintf(savedata,"%s%lf\n", "The magnitude of the Complex number is: ", magnitude);
	fprintf(savedata,"%s%lf\n", "The phase of the Complex number is: ", Zphase);
	fprintf(savedata,"%s%d\n", "The number of poles of the Chebyshev filter is: ", n_poles); 
	fprintf(savedata,"%s%d\n", "The width of the ellipse is: ", by); 
	fprintf(savedata,"%s%d\n", "The heigth of the ellipse is: ", ax); 
	fprintf(savedata,"%s%c\n", "The filter is: ", filterType); 
	fprintf(savedata,"\n");
	fclose(savedata);

	if ( tolower(filterType) == 'l' )
	std::cout << "The program applies a low pass filter to the Image Data " << filterType << endl;
	else if ( tolower(filterType) == 'h' ) 
	std::cout << "The program applies a high pass filter to the Image Data " << filterType << endl;

	
	// call to the constructor 'Z' so to create
	// an object of type 'Z'. The data type of 'Z'
	// is 'ZTransform2019'
	ZTransform2019 Z(m_rcxres, m_rcyres);

	// the object of type 'Z' 
	// sends a message (invokes)
	// to the method 'allocateData()'
	Z.allocateData();

	/// read image file (begin)
	// declare a file pointer
	FILE * pf;

	// open the file containing the image to
	// process. The image to process is by the
	// name of the string contained by 'imageFileName'
	if ((pf = fopen(imageFileName,"rb"))==NULL)
	{
		// alert the user and save into the log file 
		// the event that the program cannot open the 
		// file containing the image to process
		std::cout << "Cannot open file: " << imageFileName << endl;
		exit(0);

	} else { // else

	double number;

	for (int i1=0; i1 < m_rcyres; i1++) {// x dim
       	
		for (int i2=0; i2 < m_rcxres; i2++) { // y dim
		
		// at each iteration of the two for loops
		// the program reads the pixel value from the
		// file containing the image and 
		fread(&number,sizeof(double),1,pf);
		
		// assigns the pixel value 'number' to the
		// pixel value 'Z.pointer->Signal[i1][i2]'
		// where 'Z' invokes the pointer to the 
		// image 'Signal' at the matrix location '[i1][i2]'
		Z.pointer->Signal[i1][i2] = (double)number;
                          
		} // y dim
        
	}  // x dim 

    // close the file containg the image to process 	
    fclose (pf);


	} // else 
	/// read image file (end)

	std::cout << "Image data loaded" << endl; 

	// save all of the images
	// the object 'Z' invokes (sends a message)
	// the method by the name of 'save()'
	Z.save(); 

	std::cout << "Now calculating the Direct Z Transform..." << endl;
    OnZTransform(imageFileName, m_rcxres, m_rcyres, m_Real, m_Imaginary);
	
    std::cout << "Now calculating the Transfer Function (TF)..." << endl;
    OnTransferFunction(m_rcxres, m_rcyres, n_poles, m_cof, m_eps, m_Real, m_Imaginary, ax, by);

	std::cout << "Now calculating the Direct Z Transform of TF..." << endl;
    OnZTransform_scale("TF.img", m_rcxres, m_rcyres, m_Real, m_Imaginary);

    std::cout << "Now calculating the Inverse Z Transform..." << endl;
	OnInverseZTransformTransferFunction(imageFileName, m_rcxres, m_rcyres, m_Real, m_Imaginary);

	cout << "The Chebyshev filter was calculated" << endl;

	std::cout << "Now calculating the Direct Fourier Transform of the Image..." << endl;
	OnFourierTransform(imageFileName, m_rcxres, m_rcyres);

	char reconFilename[300];
	sprintf(reconFilename, "%s%s", "FilteredSignal-", imageFileName);

	std::cout << "Now calculating the Direct Fourier Transform of the Filtered Image..." << endl;
	OnFourierTransform(reconFilename, m_rcxres, m_rcyres);

	// alert the user of the end of the program
	std::cout << "End of Computation..." << endl;
	std::cout << endl;

	// delete the memory address
	// allocated to the images
	// do this by the command 'delete'
	// applied to the object 'Z' which
	// invokes the pointer to the data
	// structure 'data' containing the image
	// 'Signal'
	delete Z.pointer;

	// the object 'Z' invokes the
	// class destructor
	Z.~ZTransform2019();

	} // processing (end)

	return 0;
	} // run the program (end)

}// main

void OnZTransform_scale(char imageFilename[], int rcxres, int rcyres, double m_Real, double m_Imaginary)
{

	int NofXpixels = rcxres;
	int NofYpixels = rcyres;

	int i, j, index;
	int dx, dy;
	int ds, dp;
	int k2, k3, w, t;

	double pi = 3.141592;

	double * ZSpaceR = 0;
	double * ZSpaceI = 0;
	double * Signal = 0;

	FILE * logfile;

	char logfilename[128] = "Z-T.log";

	if ((logfile = fopen(logfilename, "w+")) == NULL)
	{

		printf("%s\n %s\n", "Unable to open log File", "Now Exit");

		exit(0);

	}
	else { // allocate memory 


		if ((ZSpaceR = (double *)calloc(NofXpixels*NofYpixels, sizeof(double))) == NULL)
		{

			fprintf(logfile, "%s\n", "Not enough memory to allocate Real Image data: Exit");

			exit(0);

		}

		if ((ZSpaceI = (double *)calloc(NofXpixels*NofYpixels, sizeof(double))) == NULL)
		{

			fprintf(logfile, "%s\n", "Not enough memory to allocate Real Image data: Exit");

			// FIFO memory deallocation method
			free(ZSpaceR);
			exit(0);

		}

		if ((Signal = (double *)calloc(NofXpixels*NofYpixels, sizeof(double))) == NULL)
		{

			fprintf(logfile, "%s\n", "Not enough memory to allocate Real Image data: Exit");

			// FIFO memory deallocation method
			free(ZSpaceR);
			free(ZSpaceI);
			exit(0);

		}

	} // allocate memory 

	//// read image data and initialize pointers
	double number = 0.0;

	for (i = 0; i < NofYpixels; i++)
	{
		for (j = 0; j < NofXpixels; j++)
		{

			index = ((j*NofYpixels) + i);

			*(ZSpaceR + index) = (double) 0.0;

			*(ZSpaceI + index) = (double) 0.0;

		}

	}

	FILE * pf;
	char SignalFilename[128];
	double readData;

	sprintf(SignalFilename, "%s", imageFilename);

	if ((pf = fopen(SignalFilename, "rb+")) == NULL)
	{

		fprintf(logfile, "%s\n", "Cannot open file to read Signal");

		// FIFO memory deallocation method
		free(ZSpaceR);
		free(ZSpaceI);
		free(Signal);

		exit(0);

	}
	else { // read data


		for (i = 0; i < rcyres; i++)
		{ ///read signal data
			for (j = 0; j < rcxres; j++)
			{

				index = ((j*rcyres) + i);

				fread(&readData, sizeof(double), 1, pf);

				*(Signal + index) = (double)readData;

			}
		} ///read signal data

		fprintf(logfile, "%s\n", "Signal Read in DOUBLE (64bits) format");

		fclose(pf);
	} // save data


	double phase;
	double exponent, r;
	double complexRZ, complexIZ;

	double magnitude = (double)sqrt((double)m_Real*m_Real + (double)m_Imaginary*m_Imaginary);
	double Zphase = (double)2.0*pi*atan2((double)m_Imaginary, (double)m_Real) / ((double)NofXpixels*NofYpixels);

	///// Z Transform //////
	for (i = 0; i < NofYpixels; i++)
	{ ///calculate Z-Space data

		for (j = 0; j < NofXpixels; j++)
		{


			dx = ((int)i - NofYpixels / 2);
			dy = ((int)j - NofXpixels / 2);

			k2 = ((int)(dy*NofYpixels) + dx);

			w = ((j*NofYpixels) + i);

			for (int s = 0; s < NofYpixels; s++)
			{ ///calculate Z-Space data 
				for (int p = 0; p < NofXpixels; p++)
				{


					ds = ((int)s - NofYpixels / 2);
					dp = ((int)p - NofXpixels / 2);

					k3 = ((int)(ds*NofXpixels) + dp);

					t = ((p*NofYpixels) + s);


					phase = ((double)(2.0 * pi * k2 * k3) / ((double)NofXpixels*NofYpixels));

					exponent = (double) 2.0 * pi * t * (double)Zphase / ((double)pow((double)NofXpixels*NofYpixels, 2.0));

					exponent = (double)fabs((double)exponent);

					r = (double)pow((double)magnitude, -(double)exponent);


					complexRZ = (double)cos((double)phase) + (double)sin((double)phase);

					complexIZ = -(double)sin((double)phase) + (double)cos((double)phase);


					*(ZSpaceR + w) += (double)*(Signal + t) * (double)complexRZ * (double)r;

					*(ZSpaceI + w) += (double)*(Signal + t) * (double)complexIZ * (double)r;
				}

			}///calculate Z-Space data 


		}
	} ///calculate Z-Space data
	///// Z Transform //////



	//// Procedure to scale (begin)
	double max = *(ZSpaceR);
	double min = *(ZSpaceR);

	/// compute max and min of data (begin)
	for (i = 0; i < rcyres; i++)
	{
		for (j = 0; j < rcxres; j++)
		{

			w = ((j*NofYpixels) + i);

			if (*(ZSpaceR + w) > (double)max)

				max = (double) *(ZSpaceR + w);

			if (*(ZSpaceR + w) < (double)min)

				min = (double) *(ZSpaceR + w);

		} // y dim

	}  // x dim
	/// compute max and min of data (end)

	for (i = 0; i < rcyres; i++)
	{
		for (j = 0; j < rcxres; j++)
		{

			w = ((j*NofYpixels) + i);

			if (max == min) *(ZSpaceR + w) = (double)0.0;

			else {

				*(ZSpaceR + w) = (double)fabs((min - (double)*(ZSpaceR + w)) / (min - max));

				*(ZSpaceR + w) *= ft_SCALE_z;

			}

		} // y dim

	}  // x dim
	//// Procedure to scale (end)

	//// Procedure to scale (begin)
	max = *(ZSpaceI);
	min = *(ZSpaceI);

	/// compute max and min of data (begin)
	for (i = 0; i < rcyres; i++)
	{
		for (j = 0; j < rcxres; j++)
		{

			w = ((j*NofYpixels) + i);

			if (*(ZSpaceI + w) > (double)max)

				max = (double) *(ZSpaceI + w);

			if (*(ZSpaceI + w) < (double)min)

				min = (double) *(ZSpaceI + w);

		} // y dim

	}  // x dim
	/// compute max and min of data (end)

	for (i = 0; i < rcyres; i++)
	{
		for (j = 0; j < rcxres; j++)
		{

			w = ((j*NofYpixels) + i);

			if (max == min) *(ZSpaceI + w) = (double)0.0;

			else {

				*(ZSpaceI + w) = (double)fabs((min - (double)*(ZSpaceI + w)) / (min - max));

				*(ZSpaceI + w) *= ft_SCALE_z;

			}

		} // y dim

	}  // x dim
	//// Procedure to scale (end)


	double savedata = 0.0;
	char Zfilename[128];

	sprintf(Zfilename, "%s%s", "Z-SpaceR-", imageFilename);

	fprintf(logfile, "%s\t%s\n", "Now Saving Z-Space Signal (Real) in File: ", Zfilename);

	if ((pf = fopen(Zfilename, "wb+")) == NULL)
	{

		fprintf(logfile, "%s\n", "Cannot open file to save Z-Space Signal");


		// FIFO memory deallocation method
		free(ZSpaceR);
		free(ZSpaceI);
		free(Signal);

		exit(0);

	}
	else { // save data


		for (i = 0; i < NofYpixels; i++)
		{ ///save Z-Space data
			for (j = 0; j < NofXpixels; j++)
			{

				index = ((j*NofYpixels) + i);

				savedata = (double)*(ZSpaceR + index);

				fwrite(&savedata, sizeof(double), 1, pf);

			}
		} ///save Z-Space data

		fprintf(logfile, "%s\n", "Z-Space Signal (Real) Saved");

		fclose(pf);
	} // save data



	sprintf(Zfilename, "%s%s", "Z-SpaceI-", imageFilename);

	fprintf(logfile, "%s\t%s\n", "Now Saving Z-Space Signal (Imaginary) in File: ", Zfilename);

	if ((pf = fopen(Zfilename, "wb+")) == NULL)
	{

		fprintf(logfile, "%s\n", "Cannot open file to save Z-Space Signal");

		// FIFO memory deallocation method
		free(ZSpaceR);
		free(ZSpaceI);
		free(Signal);

		exit(0);

	}
	else { // save data


		for (i = 0; i < NofYpixels; i++)
		{ ///save Z-Space data
			for (j = 0; j < NofXpixels; j++)
			{

				index = ((j*NofYpixels) + i);

				savedata = (double)*(ZSpaceI + index);

				fwrite(&savedata, sizeof(double), 1, pf);

			}
		} ///save Z-Space data

		fprintf(logfile, "%s\n", "Z-Space Signal (Imaginary) Saved");

		fclose(pf);

	} // save data

	sprintf(Zfilename, "%s%s", "Z-SpaceM-", imageFilename);

	fprintf_s(logfile, "%s\t%s\n", "Now Saving Z-Space Magnitude of the Signal in File: ", Zfilename);

	if ((pf = fopen(Zfilename, "wb+")) == NULL)
	{

		fprintf_s(logfile, "%s\n", "Cannot open file to save Z-Space Magnitude of the Signal");

		// FIFO memory deallocation method
		free(ZSpaceR);
		free(ZSpaceI);
		free(Signal);

		exit(0);

	}
	else { // save data	

	 // save a zero image (begin)
		for (int s = 0; s < NofYpixels; s++)
		{
			for (int p = 0; p < NofXpixels; p++)
			{

				savedata = (double)0.0;

				fwrite(&savedata, sizeof(double), 1, pf);

			}
		} // save a zero image (end)

		fclose(pf);

	}

	if ((pf = fopen(Zfilename, "wb+")) == NULL)
	{

		fprintf_s(logfile, "%s\n", "Cannot open file to save Z-Space Magnitude of the Signal");

		// FIFO memory deallocation method
		free(ZSpaceR);
		free(ZSpaceI);
		free(Signal);

		exit(0);

	}
	else { // save data

	 // Z-Space Magnitude (begin)
		for (int s = 0; s < (int)NofYpixels; s++)
		{
			for (int p = 0; p < (int)NofXpixels; p++)
			{


				index = ((p*NofYpixels) + s);

				savedata = (double)sqrt((double)*(ZSpaceR + index)*(double)*(ZSpaceR + index) +
					                    (double)*(ZSpaceI + index)*(double)*(ZSpaceI + index));

				fwrite(&savedata, sizeof(double), 1, pf);

			}
		} // Z-Space Magnitude (end)

		fprintf_s(logfile, "%s\n", "Z-Space Magnitude of the Signal Saved");

		fclose(pf);
	} // save data

	printf("%s\n", "Z Processing Completed");
	fprintf_s(logfile, "%s\n", "Z Processing Completed");

	fclose(logfile);


	// FIFO memory deallocation method
	free(ZSpaceR);
	free(ZSpaceI);
	free(Signal);

}

void OnZTransform(char imageFilename[], int rcxres, int rcyres, double m_Real, double m_Imaginary)
{
	
	int NofXpixels = rcxres;
	int NofYpixels = rcyres;

	int i, j, index;
	int dx, dy;
	int ds, dp; 
	int k2, k3, w, t;
	
	double pi = 3.141592;

	double * ZSpaceR = 0;
	double * ZSpaceI = 0;
	double * Signal = 0;

	FILE * logfile;
	
	char logfilename[128]="Z-T.log";

  	if ((logfile = fopen(logfilename,"w+"))==NULL)
	{

		printf("%s\n %s\n" , "Unable to open log File", "Now Exit");

		exit(0);
	
	} else { // allocate memory 


	if ((ZSpaceR = (double *) calloc( NofXpixels*NofYpixels, sizeof(double)) ) == NULL)
	{
   
		fprintf(logfile,"%s\n", "Not enough memory to allocate Real Image data: Exit");
   
		exit(0);

	}

	if ((ZSpaceI = (double *) calloc( NofXpixels*NofYpixels, sizeof(double)) ) == NULL)
	{
   
		fprintf(logfile,"%s\n", "Not enough memory to allocate Real Image data: Exit");

		// FIFO memory deallocation method
		free(ZSpaceR);
		exit(0);

	}

	if ((Signal = (double *) calloc( NofXpixels*NofYpixels, sizeof(double)) ) == NULL)
	{
   
		fprintf(logfile,"%s\n", "Not enough memory to allocate Real Image data: Exit");

		// FIFO memory deallocation method
		free(ZSpaceR);
		free(ZSpaceI);
		exit(0);

	}

	} // allocate memory 

	//// read image data and initialize pointers
	double number = 0.0;

		for (i=0; i<NofYpixels; i++)
		{ 
			for (j=0; j<NofXpixels; j++)
			{

				index = ((j*NofYpixels)+i);
				
				*(ZSpaceR+index) = (double) 0.0;

				*(ZSpaceI+index) = (double) 0.0;

			}

		}

	FILE * pf;
	char SignalFilename[128];
	double readData;
	
	sprintf(SignalFilename, "%s", imageFilename);

	if ((pf = fopen(SignalFilename,"rb+"))==NULL)
	{

	 fprintf(logfile, "%s\n", "Cannot open file to read Signal");

	 // FIFO memory deallocation method
	 free(ZSpaceR);
	 free(ZSpaceI);
	 free(Signal);

	 exit(0);
	
	} else { // read data


	for (i=0; i<rcyres; i++)
	{ ///read signal data
		for (j=0; j<rcxres; j++)
		{

			index = ((j*rcyres)+i);
          
            fread(&readData,sizeof(double),1,pf);

			*(Signal+index) = (double)readData;

		}
	} ///read signal data

	fprintf(logfile,"%s\n", "Signal Read in DOUBLE (64bits) format");

	fclose (pf);
	} // save data


	double phase;
	double exponent, r;
	double complexRZ, complexIZ;
		
	double magnitude = (double) sqrt ( (double)m_Real*m_Real + (double)m_Imaginary*m_Imaginary );
	double Zphase = (double)2.0*pi*atan2( (double)m_Imaginary, (double)m_Real ) / ((double)NofXpixels*NofYpixels);

	///// Z Transform //////
	for (i=0; i<NofYpixels; i++)
	{ ///calculate Z-Space data

		for (j=0; j<NofXpixels; j++)
		{

	
			dx = ((int) i - NofYpixels/2);
		    dy = ((int) j - NofXpixels/2);

			k2 = ((int)(dy*NofYpixels)+dx); 

			w = ((j*NofYpixels)+i);

			for (int s=0; s<NofYpixels; s++)
			{ ///calculate Z-Space data 
				for (int p=0; p<NofXpixels; p++)
				{ 
					

		     		ds = ((int) s - NofYpixels/2);
		            dp = ((int) p - NofXpixels/2);
 
				    k3 = ((int)(ds*NofXpixels)+dp); 

					t = ((p*NofYpixels)+s);


		 		    phase = ((double) (2.0 * pi * k2 * k3) / ((double)NofXpixels*NofYpixels));

					exponent = (double) 2.0 * pi * t * (double)Zphase / ((double) pow((double)NofXpixels*NofYpixels, 2.0));

					exponent = (double)fabs((double)exponent);

					r = (double) pow( (double)magnitude, -(double)exponent );


					complexRZ = (double) cos( (double)phase ) + (double) sin( (double)phase );
					
					complexIZ = -(double) sin( (double)phase ) + (double) cos( (double)phase ); 

					
					*(ZSpaceR+w) += (double)*(Signal+t) * (double)complexRZ * (double)r; 

					*(ZSpaceI+w) += (double)*(Signal+t) * (double)complexIZ * (double)r;
			}

		}///calculate Z-Space data 

			    
		}
	} ///calculate Z-Space data
	///// Z Transform //////

	double savedata = 0.0;
	char Zfilename[128];

	sprintf(Zfilename, "%s%s", "Z-SpaceR-", imageFilename);

    fprintf(logfile, "%s\t%s\n", "Now Saving Z-Space Signal (Real) in File: ", Zfilename);

    if ((pf = fopen(Zfilename,"wb+"))==NULL)
	{

	 fprintf(logfile, "%s\n", "Cannot open file to save Z-Space Signal");


	 // FIFO memory deallocation method
 	 free(ZSpaceR);
 	 free(ZSpaceI);
	 free(Signal);

	 exit(0);
	
	} else { // save data


	for (i=0; i<NofYpixels; i++)
	{ ///save Z-Space data
		for (j=0; j<NofXpixels; j++)
		{

			index = ((j*NofYpixels)+i);

			savedata = (double)*(ZSpaceR+index);
          
            fwrite(&savedata,sizeof(double),1,pf);

		}
	} ///save Z-Space data

	fprintf(logfile,"%s\n", "Z-Space Signal (Real) Saved");

	fclose (pf);
	} // save data



	sprintf(Zfilename, "%s%s", "Z-SpaceI-", imageFilename);

    fprintf(logfile, "%s\t%s\n", "Now Saving Z-Space Signal (Imaginary) in File: ", Zfilename);

    if ((pf = fopen(Zfilename,"wb+"))==NULL)
	{

	 fprintf(logfile, "%s\n", "Cannot open file to save Z-Space Signal");

	 // FIFO memory deallocation method
	 free(ZSpaceR);
	 free(ZSpaceI);
	 free(Signal);

	 exit(0);
	
	} else { // save data


	for (i=0; i<NofYpixels; i++)
	{ ///save Z-Space data
		for (j=0; j<NofXpixels; j++)
		{

			index = ((j*NofYpixels)+i);

			savedata = (double)*(ZSpaceI+index);
          
            fwrite(&savedata,sizeof(double),1,pf);

		}
	} ///save Z-Space data

	fprintf(logfile,"%s\n", "Z-Space Signal (Imaginary) Saved");

	fclose (pf);
	
	} // save data

	sprintf(Zfilename, "%s%s", "Z-SpaceM-", imageFilename);

    fprintf_s(logfile, "%s\t%s\n", "Now Saving Z-Space Magnitude of the Signal in File: ", Zfilename);

    if ((pf = fopen(Zfilename,"wb+"))==NULL)
	{

	 fprintf_s(logfile, "%s\n", "Cannot open file to save Z-Space Magnitude of the Signal");

	 // FIFO memory deallocation method
	 free(ZSpaceR);
	 free(ZSpaceI);
	 free(Signal);

	 exit(0);
	
	} else { // save data	

		// save a zero image (begin)
		for (int s=0; s<NofYpixels; s++)
		{ 
			for (int p=0; p<NofXpixels; p++)
			{ 

			savedata = (double)0.0;
          
            fwrite(&savedata,sizeof(double),1,pf);

			}
		} // save a zero image (end)

	fclose(pf);
	
	}
		
	if ((pf = fopen(Zfilename,"wb+"))==NULL)
	{

	 fprintf_s(logfile, "%s\n", "Cannot open file to save Z-Space Magnitude of the Signal");

	 // FIFO memory deallocation method
	 free(ZSpaceR);
	 free(ZSpaceI);
	 free(Signal);

	 exit(0);
	
	} else { // save data
		
		// Z-Space Magnitude (begin)
		for (int s=0; s<(int)NofYpixels; s++)
		{ 
			for (int p=0; p<(int)NofXpixels; p++)
			{ 
			
		
			index = ((p*NofYpixels)+s);

			savedata = (double) sqrt( (double)*(ZSpaceR+index)*(double)*(ZSpaceR+index) + 
		   		                      (double)*(ZSpaceI+index)*(double)*(ZSpaceI+index) );
          
            fwrite(&savedata,sizeof(double),1,pf);
			
		}
	} // Z-Space Magnitude (end)

	fprintf_s(logfile,"%s\n", "Z-Space Magnitude of the Signal Saved");

	fclose (pf);
	} // save data

	printf("%s\n", "Z Processing Completed");
    fprintf_s(logfile,"%s\n", "Z Processing Completed");

	fclose(logfile);
	

	// FIFO memory deallocation method
	free(ZSpaceR);
	free(ZSpaceI);
	free(Signal);

}

void OnTransferFunction(int rcxres, int rcyres, int n_poles, double m_cof, double m_eps, double m_Real, double m_Imaginary, int ax, int by)
{
	
	int NofXpixels = rcxres;
	int NofYpixels = rcyres;

	int i, j, index;
	int ds, dp, t; 
	
	double pi = 3.141592;
	
	double * tf = 0;
	FILE * logfile;
	
	char filenamelog[128]="Chebyshev.log";

	if ((logfile = fopen(filenamelog,"w+"))==NULL)
	{

	fprintf(logfile,"%s\n", "Unable to open log file, now exit...");
	exit(0);
	
	} else { // run the Filtering Process (begin) 
	
	
	if ((tf = (double *) calloc( NofXpixels*NofYpixels, sizeof(double)) ) == NULL)
	{
   
		fprintf(logfile,"%s\n", "Not enough memory to allocate Real Image data: Exit");

		exit(0);

	}

		struct ChebyshevPoles {

		double *spmR; // pointer to the matrix entry

		double *spmI; // pointer to the matrix entry

		double *spm; // pointer to the matrix entry

	}*Chebyshev_pointer; // pointer to the matrices
	

	 // (1) allocate struct 'data' (begin)
	 Chebyshev_pointer = new ChebyshevPoles;

	 Chebyshev_pointer->spmR = new double[n_poles+1];

	 Chebyshev_pointer->spmI = new double[n_poles+1];

	 Chebyshev_pointer->spm = new double[n_poles+1];

    	// (2) initialize (begin)
		for( int v=1; v <= n_poles; v++ ) { // (a)

			Chebyshev_pointer->spmR[v] = (double)0.0;

			Chebyshev_pointer->spmI[v] = (double)0.0;

			Chebyshev_pointer->spm[v] = (double)0.0;

		 } //(a)
		// (2) initialize (end)

		double eps = ((double)1.0/m_eps); // ripple factor is m_eps
		// cannot be zero as per data input to the program

		// calculate Chebyshev Space
		for (i = 1; i <= n_poles; i++)
		{ 
			
				double thetam = (pi / 2.0) * ((double)2 * i - 1.0) / ( n_poles );
				
				// calculate negative pole only to use in the transfer function
				double argument = ((double)1.0 / ( n_poles )) * 
					              
					               log( (double) eps  + sqrt( ((double) eps*eps ) + 1.0 ) );
				

				double sinh = ( (double) exp ( (double) argument ) - (double) exp ( (double) -argument ) ) / 2.0;

				double cosh = ( (double) exp ( (double) argument ) + (double) exp ( (double) -argument ) ) / 2.0;

				Chebyshev_pointer->spmR[i] = -(double)sinh * (double) sin ( (double) thetam );

				Chebyshev_pointer->spmI[i] = (double)cosh * (double) cos ( (double) thetam ); 

		}

	FILE * opf;
	char ofilename[328];
	double savedata;

	sprintf(ofilename, "%s", "ChebyshevR.img");

    fprintf(logfile, "%s\t%s\n", "Now Saving Chebyshev Real Space in File: ", ofilename);

    if ((opf = fopen(ofilename,"wb+"))==NULL)
	{

	 fprintf(logfile, "%s\n", "Cannot open file to save Chebyshev Real Space");

	 free(tf);
	 delete Chebyshev_pointer;

	 exit(0);
	
	} else { // save data


	for (i = 1; i <= n_poles; i++)
	{ ///save Chebyshev-space data
		
			savedata = (double)Chebyshev_pointer->spmR[i];
          
            fwrite(&savedata,sizeof(double),1,opf);

		
	} ///save Chebyshev-space data

	fprintf(logfile,"%s\n", "Chebyshev Real Space Saved");

	fclose (opf);
	} // save data


	sprintf(ofilename, "%s", "ChebyshevI.img");

    fprintf(logfile, "%s\t%s\n", "Now Saving Chebyshev Imaginary Space in File: ", ofilename);

    if ((opf = fopen(ofilename,"wb+"))==NULL)
	{

	 fprintf(logfile, "%s\n", "Cannot open file to save Chebyshev Imaginary Space");

	 free(tf);
	 delete Chebyshev_pointer;

	 exit(0);
	
	} else { // save data


	for (i = 1; i <= n_poles; i++)
	{ ///save Chebyshev-space data
		
			savedata = (double)Chebyshev_pointer->spmI[i];
          
            fwrite(&savedata,sizeof(double),1,opf);

		
	} ///save Chebyshev-space data

	fprintf(logfile,"%s\n", "Chebyshev Imaginary Space Saved");

	fclose (opf);
	} // save data

	    /// calculate magnitude of the Poles
		for (int s = 1; s <= n_poles; s++)
		{ 
					
				// magnitude of Pole
				Chebyshev_pointer->spm[s] = (double) sqrt ( ((double)Chebyshev_pointer->spmR[s] * 
									 							     Chebyshev_pointer->spmR[s] ) + 
				                  		                    ((double)Chebyshev_pointer->spmI[s] * 
														 		     Chebyshev_pointer->spmI[s] ) ); 		
	    } /// calculate magnitude of the Poles

	    //// initialize pointers
		for (i=0; i<NofYpixels; i++)
		{ 
			for (j=0; j<NofXpixels; j++)
			{

				index = ((j*NofYpixels)+i);
						
				*(tf+index) = (double) 0.0;

			}

		}

	 
			double complex;
			double tf_denominator;
		
			for (int s=0; s<NofYpixels; s++)
			{ ///calculate TF-Space data 
				for (int p=0; p<NofXpixels; p++)
				{ 
					

		     		ds = ((int) s - NofYpixels/2);
		            dp = ((int) p - NofXpixels/2);

					t = ((p*NofYpixels)+s);


					double phase = (double)2.0 * pi * atan2((double)m_Imaginary, (double)m_Real);

					double magnitude = (double)sqrt((double)(((double)ds * ds / ax) + ((double)dp * dp / by)));

					double complexR = (double)magnitude * (double)cos((double)phase);
					double complexI = (double)magnitude * (double)sin((double)phase);
			
					double samplingPeriod = 2.0 * pi * (double)pow(((double)NofXpixels * NofYpixels), 1.0/m_cof);

					double T = ((double)m_cof) / ((double)tan((double)m_cof*samplingPeriod/2.0));

					// bilinear transform to change the variable from 's' to 'z'
					complex = ((double)2.0 / T) * ((double) complexR + complexI - 1.0) / ((double) complexR + complexI + 1.0);
		     				
			
				double product = 1.0;

				for (int u = 1; u <= n_poles; u++)
				{ 
					
					if ((double)Chebyshev_pointer->spmR[u] < 0)
					{
							
							product *= ( (double)complex -

								         ((double)Chebyshev_pointer->spmR[u] +

						 	              (double)Chebyshev_pointer->spmI[u]) );

					}
					else product *= (double) 1.0;
	
				 }
					
			

		if ( (double) (( pow(2.0, (n_poles - 1) ) ) * m_eps) != 0.0 && (double)product != (double) 0.0 ) {
					
			
			tf_denominator = ( ( (( (double)pow(2.0, (n_poles - 1) ) ) * m_eps)) * 
						                     
		 				         ((double)product) );

			if ( (_isnan( (double) tf_denominator) ) == 0 ) { 					

			*(tf+t) = (double) 1.0 / ( ( (( (double)pow(2.0, (n_poles - 1) ) ) * m_eps)) * 
						                     
			                          ((double)product) );
			
					} else { *(tf+t) = (double) 0.0; }

				    } else { *(tf+t) = (double) 0.0; }
					
			   }

  		   }///calculate TF-Space data 
       	   ///// TF //////


			//// Procedure to scale the filter (begin)
			// scale tf (begin) 
			double max = *(tf);
			double min = *(tf);

			/// compute max and min of data (begin)
			for (i = 0; i < rcyres; i++)
			{
				for (j = 0; j < rcxres; j++)
				{

					index = ((j*rcyres) + i);

					if (*(tf + index) > (double)max)

						max = (double) *(tf + index);

					if (*(tf + index) < (double)min)

						min = (double) *(tf + index);

				} // y dim

			}  // x dim
			/// compute max and min of data (end)

			if ( tolower(filterType) == 'l' ) {

			// scale (begin)
			for (i = 0; i < rcyres; i++)
			{
				for (j = 0; j < rcxres; j++)
				{

					index = ((j*rcyres) + i);

					if (max == min) *(tf + index) = (double)0.0;

					else {

						*(tf + index) = (double)fabs((min - (double)*(tf + index)) / (min - max));

						*(tf + index) *= ft_SCALE;

					}

				} // y dim

			}  // x dim
			
			} else if ( tolower(filterType) == 'h' ) {

			// scale (begin)
			for (i = 0; i < rcyres; i++)
			{
				for (j = 0; j < rcxres; j++)
				{

					index = ((j*rcyres) + i);

					if (max == min) *(tf + index) = (double)0.0;

					else {

						// HP = 1.0 - LP
						*(tf + index) = (double) 1.0 - (double)fabs((min - (double)*(tf + index)) / (min - max));

						*(tf + index) *= ft_SCALE;

					}

				} // y dim

			}  // x dim
		    // scale (end)
		} //// Procedure to scale the filter (end)
	

	char filename[128];
	FILE * pf;

	sprintf(filename, "%s", "TF.img");

    fprintf(logfile, "%s\t%s\n", "Now Saving TF in File: ", filename);

    if ((pf = fopen(filename,"wb+"))==NULL)
	{

	 fprintf(logfile, "%s\n", "Cannot open file to save TF");

	 // FIFO memory deallocation method
	 free(tf);
	////////// free(product);
	 delete Chebyshev_pointer;

	 exit(0);
	
	} else { // save data


	for (i=0; i<NofYpixels; i++)
	{ ///save TF data
		for (j=0; j<NofXpixels; j++)
		{

			index = ((j*NofYpixels)+i);

			savedata = (double)*(tf+index);
          
            fwrite(&savedata,sizeof(double),1,pf);

		}
	} ///save Z-Space data

	fprintf(logfile,"%s\n", "TF Saved");

	fclose (pf);
	} // save data


	printf("%s\n", "TF Processing Completed");
    fprintf_s(logfile,"%s\n", "TF Processing Completed");

	fclose(logfile);
	

	 // FIFO memory deallocation method
	 free(tf);
	 delete Chebyshev_pointer;

	 } // run the Filtering Process (ends) 

}

void OnInverseZTransformTransferFunction(char filename[], int rcxres, int rcyres, double m_Real, double m_Imaginary)
{
	
	int NofXpixels = rcxres;
	int NofYpixels = rcyres;
	
	int i, j, index;
	int dx, dy;
	int ds, dp; 
	int k2, k3, w, t;
	
	double pi = 3.141592;
	
	double phase;

	//2010
	double emittingSource = 1.4145; // 2021
	double scale = ((double)rcxres*rcyres*emittingSource); 
	//2010

	FILE * logfile;
	char logfilename[128]="INV-ZT.log";

	FILE *image;
	char imageFilename[256];

	double * ZSpaceR = 0;
	double * ZSpaceI = 0;
	double * reconSignal = 0;
	double * transferFR = 0;
	double * transferFI = 0;

	if ((logfile = fopen(logfilename,"w+"))==NULL)
	{

	 exit(0);
	
	} else { // allocate memory

		
	printf("%s\n", "Now INV Z Processing...");
    fprintf(logfile,"%s\n", "Now INV Z Processing...");

	if ((ZSpaceR = (double *) calloc( NofXpixels*NofYpixels, sizeof(double)) ) == NULL)
	{
   
		fprintf(logfile,"%s\n", "Not enough memory to allocate Real Image data: Exit");
   
		exit(0);

	}

	if ((ZSpaceI = (double *) calloc( NofXpixels*NofYpixels, sizeof(double)) ) == NULL)
	{
   
		fprintf(logfile,"%s\n", "Not enough memory to allocate Real Image data: Exit");
   
		// FIFO memory deallocation method
		free(ZSpaceR);
		exit(0);

	}


	if ((reconSignal = (double *) calloc( NofXpixels*NofYpixels, sizeof(double)) ) == NULL)
	{
	
		fprintf(logfile,"%s\n", "Not enough memory to allocate Imaginary Image data: Exit");
	
		// FIFO memory deallocation method
		free(ZSpaceR);
		free(ZSpaceI);

		exit(0);

	}

	if ((transferFR = (double *) calloc( NofXpixels*NofYpixels, sizeof(double)) ) == NULL)
	{
   
		fprintf(logfile,"%s\n", "Not enough memory to allocate Real Image data: Exit");
        
		free(ZSpaceR);
		free(ZSpaceI);
		free(reconSignal);
				
		exit(0);

	}

	if ((transferFI = (double *) calloc( NofXpixels*NofYpixels, sizeof(double)) ) == NULL)
	{
   
		fprintf(logfile,"%s\n", "Not enough memory to allocate Real Image data: Exit");
   
		// FIFO memory deallocation method
		free(ZSpaceR);
		free(ZSpaceI);
		free(reconSignal);
		free(transferFR);

		exit(0);

	}

	} // allocate memory

	
	//// read image data and initialize pointers
    sprintf(imageFilename, "%s%s", "Z-SpaceR-", filename);

    if ((image = fopen(imageFilename,"rb+"))==NULL)
	{
	
	 fprintf(logfile, "%s%s\n", "Cannot open Image File: ", imageFilename);
	 
	 // FIFO memory deallocation method
	 free(ZSpaceR);
	 free(ZSpaceI);
	 free(reconSignal);
	 free(transferFR);
	 free(transferFI);

	 exit(0);

	} else { // read data and initialize pointers

		double number = 0.0;

		for (i=0; i<NofYpixels; i++)
		{ 
			for (j=0; j<NofXpixels; j++)
			{

				index = ((j*NofYpixels)+i);

				fread(&number,sizeof(double),1,image);
				
				*(ZSpaceR+index) = (double) number;

		
			}

		}

		fclose(image);

	}// read data and initialize pointers


    char imageFilename2[128];

	sprintf(imageFilename2, "%s%s", "Z-SpaceI-", filename);


    if ((image = fopen(imageFilename2,"rb+"))==NULL)
	{
	
	 fprintf(logfile, "%s%s\n", "Cannot open Image File: ", imageFilename2);

	 // FIFO memory deallocation method
	 free(ZSpaceR);
	 free(ZSpaceI);
	 free(reconSignal);
	 free(transferFR);
	 free(transferFI);
	
	 exit(0);

	} else { // read data and initialize pointers

		double number = 0.0;

		for (i=0; i<NofYpixels; i++)
		{ 
			for (j=0; j<NofXpixels; j++)
			{

				index = ((j*NofYpixels)+i);

				fread(&number,sizeof(double),1,image);
				
				*(ZSpaceI+index) = (double) number;

			}

		}

		fclose(image);


		for (i=0; i<NofYpixels; i++)
		{ 
			for (j=0; j<NofXpixels; j++)
			{

				index = ((j*NofYpixels)+i);

				*(reconSignal+index) = (double)0.0;
					
			}

		}


	}// read data and initialize pointers


	//// read image data and initialize pointers
    sprintf(imageFilename, "%s", "Z-SpaceR-TF.img");

    if ((image = fopen(imageFilename,"rb+"))==NULL)
	{
	
	 fprintf(logfile, "%s%s\n", "Cannot open Image File: ", imageFilename);
	 
	 // FIFO memory deallocation method
	 free(ZSpaceR);
	 free(ZSpaceI);
	 free(reconSignal);
	 free(transferFR);
	 free(transferFI);
	
	 exit(0);

	} else { // read data and initialize pointers

		double number = 0.0;

		for (i=0; i<NofYpixels; i++)
		{ 
			for (j=0; j<NofXpixels; j++)
			{

				index = ((j*NofYpixels)+i);

				fread(&number,sizeof(double),1,image);
				
				*(transferFR+index) = (double) number;

		
			}

		}

		fclose(image);

	}// read data and initialize pointers

	//// read image data and initialize pointers
    sprintf(imageFilename, "%s", "Z-SpaceI-TF.img");

    if ((image = fopen(imageFilename,"rb+"))==NULL)
	{
	
	 fprintf(logfile, "%s%s\n", "Cannot open Image File: ", imageFilename);
	 
	 // FIFO memory deallocation method
	 free(ZSpaceR);
	 free(ZSpaceI);
	 free(reconSignal);
	 free(transferFR);
	 free(transferFI);
	
	 exit(0);

	} else { // read data and initialize pointers

		double number = 0.0;

		for (i=0; i<NofYpixels; i++)
		{ 
			for (j=0; j<NofXpixels; j++)
			{

				index = ((j*NofYpixels)+i);

				fread(&number,sizeof(double),1,image);
				
				*(transferFI+index) = (double) number;

		
			}

		}

		fclose(image);

	}// read data and initialize pointers

	
	double real = 0.0, imaginary = 0.0;
	double realComponent = 0.0, imaginaryComponent = 0.0;
	double exponent, r;

	double magnitude = (double) sqrt ( (double)m_Real*m_Real + (double)m_Imaginary*m_Imaginary );
	double Zphase = (double)2.0*pi*atan2( (double)m_Imaginary, (double)m_Real ) / ((double)NofXpixels*NofYpixels);

	
	///// INV Z Transform //////
	for (i = 0; i < NofYpixels; i++)
	{ ///process Z-Space data

		for (j = 0; j < NofXpixels; j++)
		{

			dx = ((int)i - NofYpixels / 2);
			dy = ((int)j - NofXpixels / 2);

			k2 = ((int)(dy * NofYpixels) + dx);

			w = ((j*NofYpixels) + i);


			real = (double)0.0;
			imaginary = (double)0.0;

			for (int s = 0; s < NofYpixels; s++)
			{ ///process Z-Space data

				for (int p = 0; p < NofXpixels; p++)
				{

					ds = ((int)s - NofYpixels / 2);
					dp = ((int)p - NofXpixels / 2);

					k3 = ((int)(ds * NofXpixels) + dp);

					t = ((p*NofYpixels) + s);


					phase = ((double)(2.0 * pi * k2 * k3) / ((double)NofXpixels*NofYpixels));

					exponent = (double) 2.0 * pi * t * (double)Zphase / ((double)pow((double)NofXpixels*NofYpixels, 2.0));

					exponent = (double)fabs((double)exponent);

					r = (double)pow((double)magnitude, (double)exponent);


					real += ((double) *(ZSpaceR + t) * (double) *(transferFR + t) * (double)cos((double)phase)) -
						    ((double) *(ZSpaceI + t) * (double) *(transferFI + t) * (double)sin((double)phase));

					real *= (double)r;

	
					imaginary += ((double) *(ZSpaceR + t) * (double) *(transferFR + t) * (double)sin((double)phase)) +
						         ((double) *(ZSpaceI + t) * (double) *(transferFI + t) * (double)cos((double)phase));

					imaginary *= (double)r;

				}

			}///process Z-Space data 


			realComponent = (double)real * real;

			if ((_isnan((double)realComponent)) == 0) {}

			else { realComponent = (double) 0.0; }


			imaginaryComponent = (double)imaginary * imaginary;

			if ((_isnan((double)imaginaryComponent)) == 0) {}

			else { imaginaryComponent = (double) 0.0; }



			*(reconSignal + w) = (double)sqrt(((double)realComponent) + ((double)imaginaryComponent));

			*(reconSignal + w) /= (double)scale;

		}
	} ///process Z-Space data

	double savedata = 0.0;
	FILE * pf;
	char reconFilename[128];

	sprintf(reconFilename, "%s%s", "FilteredSignal-", filename);


    fprintf(logfile, "%s\t%s\n", "Now Saving Filtered Signal in File: ", reconFilename);

    if ((pf = fopen(reconFilename,"wb+"))==NULL)
	{

	 fprintf(logfile, "%s\n", "Cannot open file to save Filtered Signal");

	 // FIFO memory deallocation method
	 free(ZSpaceR);
	 free(ZSpaceI);
	 free(reconSignal);
	 free(transferFR);
	 free(transferFI);

	 exit(0);
	
	} else { // save data


	for (i=0; i<NofYpixels; i++)
	{ ///save Z-Space data
		for (j=0; j<NofXpixels; j++)
		{

			index = ((j*NofYpixels)+i);

			savedata = (double)*(reconSignal+index);
          
            fwrite(&savedata,sizeof(double),1,pf);

		}
	} ///save Z-Space data

	fprintf(logfile,"%s\n", "Filtered Signal Saved");

	fclose (pf);
	} // save data
    printf("%s\n", "Inverse Z Processing Completed");
    fprintf(logfile,"%s\n", "Inverse Z Processing Completed");

	fclose(logfile);
	
		
	 // FIFO memory deallocation method
	 free(ZSpaceR);
	 free(ZSpaceI);
	 free(reconSignal);
	 free(transferFR);
	 free(transferFI);

}

void OnFourierTransform(char imageFilename[], int rcxres, int rcyres)
{

	int NofXpixels = rcxres;
	int NofYpixels = rcyres;

	int i, j, index;
	int dx, dy;
	int ds, dp;
	int k2, k3, w, t;

	double pi = 3.141592;

	double * kSpaceR = 0;
	double * kSpaceI = 0;
	double * Signal = 0;

	FILE * logfile;

	char logfilename[128] = "Fourier-T.log";

	if ((logfile = fopen(logfilename, "w+")) == NULL)
	{

		printf("%s\n %s\n", "Unable to open log File", "Now Exit");

		exit(0);

	}
	else { // allocate memory 


		if ((kSpaceR = (double *)calloc(NofXpixels*NofYpixels, sizeof(double))) == NULL)
		{

			fprintf(logfile, "%s\n", "Not enough memory to allocate Real Image data: Exit");

			exit(0);

		}

		if ((kSpaceI = (double *)calloc(NofXpixels*NofYpixels, sizeof(double))) == NULL)
		{

			fprintf(logfile, "%s\n", "Not enough memory to allocate Real Image data: Exit");

			// FIFO memory deallocation method
			free(kSpaceR);
			exit(0);

		}

		if ((Signal = (double *)calloc(NofXpixels*NofYpixels, sizeof(double))) == NULL)
		{

			fprintf(logfile, "%s\n", "Not enough memory to allocate Real Image data: Exit");

			// FIFO memory deallocation method
			free(kSpaceR);
			free(kSpaceI);
			exit(0);

		}

	} // allocate memory 

	//// read image data and initialize pointers
	double number = 0.0;

	for (i = 0; i < NofYpixels; i++)
	{
		for (j = 0; j < NofXpixels; j++)
		{

			index = ((j*NofYpixels) + i);

			*(kSpaceR + index) = (double) 0.0;

			*(kSpaceI + index) = (double) 0.0;

		}

	}

	FILE * pf;
	char SignalFilename[128];
	double readData;

	sprintf(SignalFilename, "%s", imageFilename);

	if ((pf = fopen(SignalFilename, "rb+")) == NULL)
	{

		fprintf(logfile, "%s\n", "Cannot open file to read Signal");

		// FIFO memory deallocation method
		free(kSpaceR);
		free(kSpaceI);
		free(Signal);

		exit(0);

	}
	else { // read data


		for (i = 0; i < rcyres; i++)
		{ ///read signal data
			for (j = 0; j < rcxres; j++)
			{

				index = ((j*rcyres) + i);

				fread(&readData, sizeof(double), 1, pf);

				*(Signal + index) = (double)readData;

			}
		} ///read signal data

		fprintf(logfile, "%s\n", "Signal Read in DOUBLE (64bits) format");

		fclose(pf);
	} // save data

	double phase, complexR, complexI;

	///// Fourier Transform //////
	for (i = 0; i < NofYpixels; i++)
	{ ///calculate k-space data

		for (j = 0; j < NofXpixels; j++)
		{


			dx = ((int)i - NofYpixels / 2);
			dy = ((int)j - NofXpixels / 2);

			k2 = ((int)(dy*NofYpixels) + dx);

			w = ((j*NofYpixels) + i);

			for (int s = 0; s < NofYpixels; s++)
			{ ///calculate k-space data 
				for (int p = 0; p < NofXpixels; p++)
				{


					ds = ((int)s - NofYpixels / 2);
					dp = ((int)p - NofXpixels / 2);

					k3 = ((int)(ds*NofXpixels) + dp);

					t = ((p*NofYpixels) + s);

					phase = ((double)(2.0 * pi * k2 * k3) / ((double)NofXpixels*NofYpixels));

					//** nayuki.eigenstate.org/page/how-to-implement-the-discrete-fourier-transform (begin)**/
					complexR = (double)cos((double)phase) + (double)sin((double)phase);

					complexI = -(double)sin((double)phase) + (double)cos((double)phase);
					//** nayuki.eigenstate.org/page/how-to-implement-the-discrete-fourier-transform (end)**/

					*(kSpaceR + w) += (double) *(Signal + t) * (double)complexR;

					*(kSpaceI + w) += (double) *(Signal + t) * (double)complexI;

				}

			}///calculate k-space data 


		}
	} ///calculate k-space data

	///// Fourier Transform //////
	double savedata = 0.0;
	char FTfilename[128];

	sprintf(FTfilename, "%s%s", "K-SpaceR-", imageFilename);

	fprintf(logfile, "%s\t%s\n", "Now Saving K-Space Signal (Real) in File: ", FTfilename);

	if ((pf = fopen(FTfilename, "wb+")) == NULL)
	{

		fprintf(logfile, "%s\n", "Cannot open file to save K-Space Signal");


		// FIFO memory deallocation method
		free(kSpaceR);
		free(kSpaceI);
		free(Signal);

		exit(0);

	}
	else { // save data


		for (i = 0; i < NofYpixels; i++)
		{ ///save k-space data
			for (j = 0; j < NofXpixels; j++)
			{

				index = ((j*NofYpixels) + i);

				savedata = (double)*(kSpaceR + index);

				fwrite(&savedata, sizeof(double), 1, pf);

			}
		} ///save k-space data

		fprintf(logfile, "%s\n", "K-Space Signal (Real) Saved");

		fclose(pf);
	} // save data



	sprintf(FTfilename, "%s%s", "K-SpaceI-", imageFilename);

	fprintf(logfile, "%s\t%s\n", "Now Saving K-Space Signal (Imaginary) in File: ", FTfilename);

	if ((pf = fopen(FTfilename, "wb+")) == NULL)
	{

		fprintf(logfile, "%s\n", "Cannot open file to save K-Space Signal");

		// FIFO memory deallocation method
		free(kSpaceR);
		free(kSpaceI);
		free(Signal);

		exit(0);

	}
	else { // save data


		for (i = 0; i < NofYpixels; i++)
		{ ///save k-space data
			for (j = 0; j < NofXpixels; j++)
			{

				index = ((j*NofYpixels) + i);

				savedata = (double)*(kSpaceI + index);

				fwrite(&savedata, sizeof(double), 1, pf);

			}
		} ///save k-space data

		fprintf(logfile, "%s\n", "K-Space Signal (Imaginary) Saved");

		fclose(pf);

	} // save data

	sprintf(FTfilename, "%s%s", "K-SpaceM-", imageFilename);

	fprintf_s(logfile, "%s\t%s\n", "Now Saving K-Space Magnitude of the Signal in File: ", FTfilename);

	if ((pf = fopen(FTfilename, "wb+")) == NULL)
	{

		fprintf_s(logfile, "%s\n", "Cannot open file to save K-Space Magnitude of the Signal");

		// FIFO memory deallocation method
		free(kSpaceR);
		free(kSpaceI);
		free(Signal);

		exit(0);

	}
	else { // save data

	 // K-Space Magnitude (begin)
		for (int s = 0; s < (int)NofYpixels; s++)
		{
			for (int p = 0; p < (int)NofXpixels; p++)
			{


				index = ((p*NofYpixels) + s);

				savedata = (double)sqrt((double)*(kSpaceR + index)*(double)*(kSpaceR + index) +
					(double)*(kSpaceI + index)*(double)*(kSpaceI + index));

				fwrite(&savedata, sizeof(double), 1, pf);

			}
		} // K-Space Magnitude (end)

		fprintf_s(logfile, "%s\n", "K-Space Magnitude of the Signal Saved");

		fclose(pf);
	} // save data

	printf("%s\n", "FT Processing Completed");
	fprintf_s(logfile, "%s\n", "FT Processing Completed");

	fclose(logfile);


	// FIFO memory deallocation method
	free(kSpaceR);
	free(kSpaceI);
	free(Signal);

}