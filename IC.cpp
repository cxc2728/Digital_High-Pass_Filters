#define _CRT_SECURE_NO_WARNINGS
// name of the project: IntensityCurvature
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

// declare a class by the name 'IntensityCurvature'
class IntensityCurvature {

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

		double** Signal; // declare the pointer to pointer to the matrix (image) 

		double** FOD; // declare the pointer to pointer to the matrix (image) 

		double** ICF; // declare the pointer to pointer to the matrix (image) 

	}*pointer; // pointer to the element of the structure 'data'
	// the pointer points to the memory address of the
	// pointers to pointers 

public:

	// constructor of the class 'IntensityCurvature'
	IntensityCurvature(int x, int y) : n1(x), n2(y) { pointer = 0; };

	// declare the prototype of the 
	// function 'allocateData'
	// the function belongs to the 
	// sets of methods of the class 'IntensityCurvature'
	void allocateData();

	// declare the prototype of the 
	// function 'save'
	// the function belongs to the 
	// sets of methods of the class 'IntensityCurvature'
	void save();

	// destructor of the class 'IntensityCurvature'
	~IntensityCurvature() {}

};

void IntensityCurvature::allocateData() { // allocate data


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
	pointer->Signal = new double* [this->n2];

	pointer->FOD = new double* [this->n2];

	pointer->ICF = new double* [this->n2];



	for (int v = 0; v < this->n2; v++) { // (1)
		// at each iteration of the for loop
		// assign to the pointer 'Signal[v]' the instance 
		// of the memory address of the pointer [this-n1].
		// Practically define the memory address of the 
		// columns of the matrices containing the image:
		// 'Signal.

		pointer->Signal[v] = new double[this->n1];

		pointer->FOD[v] = new double[this->n1];

		pointer->ICF[v] = new double[this->n1];

	} // (1) allocate struct 'data' (end)


  // (2) initialize (begin)
	for (int v = 0; v < this->n2; v++) { // (a)

		for (int f = 0; f < this->n1; f++) { // (b)

			// at each iteration of the two for loops
			// initializes the value of the pixel of
			// the image to zero. This is done for the
			// image 'Signal'.
			pointer->Signal[v][f] = (double)0.0;

			pointer->FOD[v][f] = (double)0.0;

			pointer->ICF[v][f] = (double)0.0;

		} //(b)

	} //(a)
   // (2) initialize (end)

} // allocate data


void IntensityCurvature::save() { // saveImages

	// declare a pointer to file
	// to be used to read the image
	FILE* savedata;
	// declare a string which contains
	// the file name of the image
	char outputFile[128];

	// assign the name string "Signal.img"
	// to the string 'outputFile'
	sprintf(outputFile, "%s", "ICF.img");

	// open the image file in write-binary mode
	if ((savedata = fopen(outputFile, "wb")) == NULL)
	{
		// alert the user of possible failure in opening the file
		std::cout << "Cannot open output file, Now Exit..." << endl;
		exit(0);

	}
	else { // (save)


		for (int v = 0; v < this->n2; v++) { // (a)

			for (int f = 0; f < this->n1; f++)

				// at each iteration of the for loop saves the pixel
				// value contained at the memory address: ' &pointer->Signal[v][f] '
				fwrite(&pointer->ICF[v][f], sizeof(double), 1, savedata);

		} // (a)

		// close the file after saving
		fclose(savedata);

	} // (save)

	// assign the name string "Signal.img"
	// to the string 'outputFile'
	sprintf(outputFile, "%s", "Signal.img");

	// open the image file in write-binary mode
	if ((savedata = fopen(outputFile, "wb")) == NULL)
	{
		// alert the user of possible failure in opening the file
		std::cout << "Cannot open output file, Now Exit..." << endl;
		exit(0);

	}
	else { // (save)


		for (int v = 0; v < this->n2; v++) { // (a)

			for (int f = 0; f < this->n1; f++)

				// at each iteration of the for loop saves the pixel
				// value contained at the memory address: ' &pointer->Signal[v][f] '
				fwrite(&pointer->Signal[v][f], sizeof(double), 1, savedata);

		} // (a)

		// close the file after saving
		fclose(savedata);

	} // (save)

	// assign the name string "Signal.img"
	// to the string 'outputFile'
	sprintf(outputFile, "%s", "FOD.img");

	// open the image file in write-binary mode
	if ((savedata = fopen(outputFile, "wb")) == NULL)
	{
		// alert the user of possible failure in opening the file
		std::cout << "Cannot open output file, Now Exit..." << endl;
		exit(0);

	}
	else { // (save)


		for (int v = 0; v < this->n2; v++) { // (a)

			for (int f = 0; f < this->n1; f++)

				// at each iteration of the for loop saves the pixel
				// value contained at the memory address: ' &pointer->Signal[v][f] '
				fwrite(&pointer->FOD[v][f], sizeof(double), 1, savedata);

		} // (a)

		// close the file after saving
		fclose(savedata);

	} // (save)
} // saveImages

// read the input parameters from the
// console command line
int main(int argc, char* argv[]) {

	// assign to the char string 'outputFile'
	// the value "IntensityCurvature.log"
	char outputFile[128] = "IntensityCurvature.log";

	// declare a pointer to a file by the
	// name 'savedata'
	FILE* savedata;

	// tell the user of the list of input parameters necessary to tun the program:
	if (argc < 6) {
		std::cout << endl;
		std::cout << "Please type the image file name" << endl;
		std::cout << "Please make sure that the image format is Analyze 'double': 64 bits real" << endl;
		std::cout << "Please enter the number of pixels along the X direction (integer)" << endl;
		std::cout << "Please enter the number of pixels along the Y direction (integer)" << endl;
		std::cout << "Please enter the resampling coordinate X (double) ]0, 1.0[" << endl;
		std::cout << "Please enter the resampling coordinate Y (double) ]0, 1.0[" << endl;
		std::cout << endl;
		exit(0);
	}

	else { // run the program (begin)

		// opens the log file which name is 
		// contained in 'outputFile', opens 
		// in write mode
		if ((savedata = fopen(outputFile, "w")) == NULL)
		{
			// alert the user of possible failure in opening the file
			std::cout << "Cannot open output file, Now Exit..." << endl;
			exit(0);

		}
		else { // processing (begin)

			// declare an array of char to contain a string
			char imageFileName[128];

			// transfer into the array 'imageFileName'
			// the image file name as per input from
			// the command console. The image file name
			// is 'argv[1]'
			sprintf(imageFileName, "%s", argv[1]);

			// reads from the command console the
			// value of the image size (number of rows
			// and number of columns)
			int n1 = atoi(argv[2]);
			int n2 = atoi(argv[3]);

			double misplacement_X = atof(argv[4]);
			double misplacement_Y = atof(argv[5]);

			if ((double)misplacement_X <= 0.0 || (double)misplacement_Y <= 0.0 ||
				(double)misplacement_X > 1.0 || (double)misplacement_Y > 1.0)
			{

				std::cout << "Please keep the misplacements in ]0, 1[" << endl;
				exit(0);
			}

			// inform the user of the image size 
			// (number of rows and number of columns
			// of the matrix containing the image)
			std::cout << endl;
			std::cout << "The number of pixels along the X direction is: " << atoi(argv[2]) << endl;
			std::cout << "The number of pixels along the Y direction is: " << atoi(argv[3]) << endl;
			std::cout << "The resampling coordinate along the X direction is: " << atof(argv[4]) << endl;
			std::cout << "The resampling coordinate along the Y direction is: " << atof(argv[5]) << endl;

			// save into the log file the image size 
			// (number of rows and number of columns
			// of the matrix containing the image)
			fprintf(savedata, "%s%s\n", "The image file name is: ", imageFileName);
			fprintf(savedata, "%s%d\n", "The number of pixels along the X direction is: ", n1);
			fprintf(savedata, "%s%d\n", "The number of pixels along the Y direction is: ", n2);
			fprintf(savedata, "%s%lf\n", "The resampling coordinate along the X direction is: ", atof(argv[4]));
			fprintf(savedata, "%s%lf\n", "The resampling coordinate along the Y direction is: ", atof(argv[5]));

			// call to the constructor 'IC' so to create
			// an object of type 'IC'. The data type of 'IC'
			// is 'IntensityCurvature'
			IntensityCurvature IC(n1, n2);

			// the object of type 'IC' 
			// sends a message (invokes)
			// to the method 'allocateData()'
			IC.allocateData();

			/// read image file (begin)
			// declare a file pointer
			FILE* pf;

			// open the file containing the image to
			// process. The image to process is by the
			// name of the string contained by 'imageFileName'
			if ((pf = fopen(imageFileName, "rb")) == NULL)
			{
				// alert the user and save into the log file 
				// the event that the program cannot open the 
				// file containing the image to process
				std::cout << "Cannot open file: " << imageFileName << endl;
				fprintf(savedata, "%s%s\n", "Cannot open file: ", imageFileName);
				exit(0);

			}
			else { // else

				double number;

				for (int i1 = 0; i1 < n2; i1++) {// x dim

					for (int i2 = 0; i2 < n1; i2++) { // y dim

						// at each iteration of the two for loops
						// the program reads the pixel value from the
						// file containing the image and 
						fread(&number, sizeof(double), 1, pf);

						// assigns the pixel value 'number' to the
						// pixel value 'IC.pointer->Signal[i1][i2]'
						// where 'IC' invokes the pointer to the 
						// image 'Signal' at the matrix location '[i1][i2]'
						IC.pointer->Signal[i1][i2] = (double)number;

					} // y dim

				}  // x dim 

				// close the file containg the image to process 	
				fclose(pf);


			} // else 
			/// read image file (end)

			std::cout << "Image data loaded" << endl;

			std::cout << "Compute Intensity-Curvature Functional" << endl;

			int PAD = 1;

			for (int i1 = PAD; i1 < n2 - PAD; i1++) {// x dim

				for (int i2 = PAD; i2 < n1 - PAD; i2++) { // y dim

					// primitive of ' IC.pointer->Signal[i1][i2] ' in dx dy
					double k = (double)IC.pointer->Signal[i1][i2] * misplacement_X * misplacement_Y +

						// primitive of ' x * thetax ' in dx dy
						(misplacement_X * misplacement_Y * misplacement_X / 2.0) *
						(IC.pointer->Signal[i1 + 1][i2] - IC.pointer->Signal[i1][i2]) +

						// primitive of ' y * thetay ' in dx dy
						(misplacement_X * misplacement_Y * misplacement_Y / 2.0) *
						(IC.pointer->Signal[i1][i2 + 1] - IC.pointer->Signal[i1][i2]) +

						// primitive of ' omega * x * y ' in dx dy
						(misplacement_X * misplacement_X * misplacement_Y * misplacement_Y / 4.0) *
						(IC.pointer->Signal[i1 + 1][i2 + 1] + IC.pointer->Signal[i1][i2] - IC.pointer->Signal[i1 + 1][i2] - IC.pointer->Signal[i1][i2 + 1]);

					// primitive of ' IC.pointer->Signal[i1][i2] ' in dx dy
					double s = (double)IC.pointer->Signal[i1][i2] * misplacement_X * misplacement_Y;


					if ((double)s == 0.0 && (double)k == 0.0) IC.pointer->ICF[i1][i2] = (double)1.0; // de l'Hopital

					else if ((double)s == 0.0 && (double)k != 0.0) IC.pointer->ICF[i1][i2] = (double)0.0;

					else if ((double)s != 0.0 && (double)k == 0.0) IC.pointer->ICF[i1][i2] = (double)0.0;

					else  if ((double)s != 0.0 && (double)k != 0.0) IC.pointer->ICF[i1][i2] = (double)s / k;


				} // y dim

			}  // x dim


			std::cout << "Intensity-Curvature Functional Calculated" << endl;


			std::cout << "Calculate First Order Derivative" << endl;

			for (int i1 = PAD; i1 < n2 - PAD; i1++) {// x dim

				for (int i2 = PAD; i2 < n1 - PAD; i2++) { // y dim

					// calculate ' thetax '
					double thetax = (IC.pointer->Signal[i1 + 1][i2] - IC.pointer->Signal[i1][i2]);

					// calculate ' thetay '
					double thetay = (IC.pointer->Signal[i1][i2 + 1] - IC.pointer->Signal[i1][i2]);

					// calculate ' omega ' 
					double omega = (IC.pointer->Signal[i1 + 1][i2 + 1] + IC.pointer->Signal[i1][i2] - IC.pointer->Signal[i1 + 1][i2] - IC.pointer->Signal[i1][i2 + 1]);

					// calculate ' dfdx '
					double dfdx = (double)thetax + (double)omega * misplacement_Y;

					// calculate ' dfdy '
					double dfdy = (double)thetay + (double)omega * misplacement_X;

					// calculate FOD
					IC.pointer->FOD[i1][i2] = (double)sqrt(((double)dfdx * dfdx) + ((double)dfdy * dfdy));

				} // y dim

			}  // x dim

			// save all of the images
			// the object 'IC' invokes (sends a message)
			// the method by the name of 'save()'
			std::cout << "First Order Derivative Calculated" << endl;
			IC.save();

			// alert the user of the end of the program
			std::cout << "End of Computation..." << endl;
			std::cout << endl;

			// save to log file
			fprintf(savedata, "%s\n", "End of Computation...");
			fprintf(savedata, "\n");

			fclose(savedata);
			// delete the memorry address
			// allocated to the images
			// do this by the command 'delete'
			// applied to the object 'IC' which
			// invokes the pointer to the data
			// structure 'data' containing the image
			// 'Signal'
			delete IC.pointer;

			// the object 'IC' invokes the
			// class destructor
			IC.~IntensityCurvature();
		} // processing (end)

	} // run the program (end)

	// ANSI C requires the 'main'
	// function returning a value: 
	// zero in this case
	return 0;
} // end of main 
