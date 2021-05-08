#pragma once
#include <fstream>
#include <string>
#include <cstring>
#include <iostream>
using namespace std;

//global varibales
double** cleanDataArray;
double** index_count_of_clusters;
int col = 0;
//preprocess will clean data and write it in preprocessed file
void preprocess(string a)
{
	fstream Read_From_File;
	ofstream write_file;
	Read_From_File.open(a);
	string Course_Grade_Points[15] = { "" };
	string Course_Code = "";
	string Course_Grade = "";
	string Read_Data = "";
	string Semester_Name = "";
	string cgpa = "";
	string warning = "";
	string First_Semester_Name = "";
	string Scnd_Semester_Name = "";
	string First_Sem_Name_Array[15] = { "" };
	string Scnd_Sem_Name_Array[15] = { "" };
	string cgpa_Warining[4] = { "" };
	int notread = 0;
	string Serial_Number = "";
	int count_comma = 0;
	int count_serial = 0;
	bool flag1, flag2;
	flag1 = false;
	flag2 = false;
	bool flag3 = false;
	bool flag4 = false;
	int Counting = 0;
	if (Read_From_File.is_open())
	{
		while (!Read_From_File.eof())
		{
			count_serial = 0;
			Course_Grade = "";
			Course_Code = "";
			Serial_Number = "";
			Semester_Name = "";
			First_Semester_Name = "";
			Scnd_Semester_Name = "";
			Read_Data = "";
			cgpa = "";
			warning = "";
			count_comma = 0;
			flag1 = false;
			flag2 = false;
			flag3 = false;
			flag4 = false;
			getline(Read_From_File, Read_Data);
			if (notread == 0)
			{
				notread++;
				write_file.open("preprocessed_Data.csv", ios::app);
				if (write_file.is_open())
				{
					write_file << "Sr.No,MT104,MT119,CS118,CL118,EE182,SL101,SS101,EE227,SS122,MT224,SS111,CS217,EL227,CL217,CGPA,Warning,CS201" << endl;
				}
				else
				{
					cout << "Cant open file" << endl;
				}
				continue;
			}

			if (Read_Data != "")
			{
				while (Read_Data[count_serial] != ',')
				{
					Serial_Number += Read_Data[count_serial];
					count_serial++;
				}
				if (Counting != stoi(Serial_Number))
				{
					if (Course_Grade_Points[14] == "-1")
					{
						for (int a = 0; a < 15; a++)
						{
							Course_Grade_Points[a] = "";
							First_Sem_Name_Array[a] = { "" };
							Scnd_Sem_Name_Array[a] = { "" };
						}
						Counting++;
						Serial_Number = "";

						for (int i = 0; i < 4; i++)
							cgpa_Warining[i] = "";
						continue;
					}
					else
					{
						write_file << Counting << ",";
						for (int i = 0; i < 14; i++)
						{
							write_file << Course_Grade_Points[i] << ",";
						}
						write_file << cgpa_Warining[2] << "," << cgpa_Warining[3] << ",";
						write_file << Course_Grade_Points[14] << "," << endl;
						for (int a = 0; a < 15; a++)
						{
							Course_Grade_Points[a] = "";
							First_Sem_Name_Array[a] = { "" };
							Scnd_Sem_Name_Array[a] = { "" };
						}
						Counting++;
						Serial_Number = "";

						for (int i = 0; i < 4; i++)
							cgpa_Warining[i] = "";
					}
				}
				//counting the course comma
				for (int i = 0; i < Read_Data.length(); i++)
				{
					if (Read_Data[i] == ',')
					{
						count_comma++;
					}

					//now finding the cgpa
					if (count_comma == 1 && flag3 == false)
					{
						flag3 = true;
						int var_Semester_Name = i + 1;
						while (Read_Data[var_Semester_Name] != ',')
						{
							Semester_Name += Read_Data[var_Semester_Name];
							var_Semester_Name++;
						}
						//now dividing the Semester Name into two halces
						bool div_Sem_Name = false;
						for (int SN = 0; SN < Semester_Name.length(); SN++)
						{
							if (Semester_Name[SN] != ' ' && div_Sem_Name == false)
							{
								First_Semester_Name += Semester_Name[SN];
							}
							if (Semester_Name[SN] == ' ')
							{
								div_Sem_Name = true;
								continue;
							}
							if (div_Sem_Name == true)
							{
								Scnd_Semester_Name += Semester_Name[SN];
							}
						}
						if (div_Sem_Name == false)
						{
							Scnd_Semester_Name = "";
						}
					}
					if (count_comma == 2 && flag1 == false)
					{
						flag1 = true;
						int var_course_code = i + 1;
						while (Read_Data[var_course_code] != ',')
						{
							Course_Code += Read_Data[var_course_code];
							var_course_code++;
						}
					}
					if (count_comma == 6 && flag2 == false)
					{

						flag2 = true;
						int var_course_grade = i + 1;
						while (Read_Data[var_course_grade] != ',')
						{
							Course_Grade += Read_Data[var_course_grade];
							var_course_grade++;
						}

					}
					if (count_comma == 8 && flag4 == false)
					{
						flag4 = true;
						int var_cpga_cal = i + 1;
						while (Read_Data[var_cpga_cal] != ',')
						{
							cgpa += Read_Data[var_cpga_cal];
							var_cpga_cal++;
						}
						var_cpga_cal++;
						warning = Read_Data[var_cpga_cal];
						if (cgpa_Warining[0] == "" && cgpa_Warining[1] == "")
						{
							cgpa_Warining[0] = First_Semester_Name;
							cgpa_Warining[1] = Scnd_Semester_Name;
							cgpa_Warining[2] = cgpa;
							cgpa_Warining[3] = warning;
						}
						else
						{
							if (cgpa_Warining[1] < Scnd_Semester_Name)
							{
								cgpa_Warining[0] = First_Semester_Name;
								cgpa_Warining[1] = Scnd_Semester_Name;
								cgpa_Warining[2] = cgpa;
								cgpa_Warining[3] = warning;
							}

							else if (cgpa_Warining[1] == Scnd_Semester_Name)
							{
								if (First_Semester_Name == "FALL")
								{
									cgpa_Warining[0] = First_Semester_Name;
									cgpa_Warining[1] = Scnd_Semester_Name;
									cgpa_Warining[2] = cgpa;
									cgpa_Warining[3] = warning;
								}
							}
						}
					}

					if (Course_Grade != "")
					{
						if (Course_Code == "MT104")
						{
							if (First_Sem_Name_Array[0] == "" && Scnd_Sem_Name_Array[0] == "")
							{
								Course_Grade_Points[0] = Course_Grade;
								First_Sem_Name_Array[0] = First_Semester_Name;
								Scnd_Sem_Name_Array[0] = Scnd_Semester_Name;
							}
							else
							{
								if (Scnd_Sem_Name_Array[0] < Scnd_Semester_Name)
								{
									Course_Grade_Points[0] = Course_Grade;
								}
								else if (Scnd_Sem_Name_Array[0] == Scnd_Semester_Name)
								{
									if (First_Semester_Name == "FALL")
									{
										Course_Grade_Points[0] = Course_Grade;
									}
								}
							}

						}
						else if (Course_Code == "MT119")
						{
							////cout << Course_Grade << endl;
							if (First_Sem_Name_Array[1] == "" && Scnd_Sem_Name_Array[1] == "")
							{
								Course_Grade_Points[1] = Course_Grade;
								First_Sem_Name_Array[1] = First_Semester_Name;
								Scnd_Sem_Name_Array[1] = Scnd_Semester_Name;
								//cout << First_Semester_Name << endl;
							}
							else
							{
								if (Scnd_Sem_Name_Array[1] < Scnd_Semester_Name)
								{
									Course_Grade_Points[1] = Course_Grade;
								}
								else if (Scnd_Sem_Name_Array[1] == Scnd_Semester_Name)
								{
									if (First_Semester_Name == "FALL")
									{
										Course_Grade_Points[1] = Course_Grade;
									}
								}
							}
							//cout << Course_Grade_Points[1] << endl;
						}
						else if (Course_Code == "CS118")
						{
							if (First_Sem_Name_Array[2] == "" && Scnd_Sem_Name_Array[2] == "")
							{
								Course_Grade_Points[2] = Course_Grade;
								First_Sem_Name_Array[2] = First_Semester_Name;
								Scnd_Sem_Name_Array[2] = Scnd_Semester_Name;
								//cout << First_Semester_Name << endl;
							}
							else
							{
								if (Scnd_Sem_Name_Array[2] < Scnd_Semester_Name)
								{
									Course_Grade_Points[2] = Course_Grade;
								}
								else if (Scnd_Sem_Name_Array[2] == Scnd_Semester_Name)
								{
									if (First_Semester_Name == "FALL")
									{
										Course_Grade_Points[2] = Course_Grade;
									}
								}
							}
						}
						else if (Course_Code == "CL118")
						{
							if (First_Sem_Name_Array[3] == "" && Scnd_Sem_Name_Array[3] == "")
							{
								Course_Grade_Points[3] = Course_Grade;
								First_Sem_Name_Array[3] = First_Semester_Name;
								Scnd_Sem_Name_Array[3] = Scnd_Semester_Name;
								//cout << First_Semester_Name << endl;
							}
							else
							{
								if (Scnd_Sem_Name_Array[3] < Scnd_Semester_Name)
								{
									Course_Grade_Points[3] = Course_Grade;
								}
								else if (Scnd_Sem_Name_Array[3] == Scnd_Semester_Name)
								{
									if (First_Semester_Name == "FALL")
									{
										Course_Grade_Points[3] = Course_Grade;
									}
								}
							}
						}
						else if (Course_Code == "EE182")
						{
							if (First_Sem_Name_Array[4] == "" && Scnd_Sem_Name_Array[4] == "")
							{
								Course_Grade_Points[4] = Course_Grade;
								First_Sem_Name_Array[4] = First_Semester_Name;
								Scnd_Sem_Name_Array[4] = Scnd_Semester_Name;
								//cout << First_Semester_Name << endl;
							}
							else
							{
								if (Scnd_Sem_Name_Array[4] < Scnd_Semester_Name)
								{
									Course_Grade_Points[4] = Course_Grade;
								}
								else if (Scnd_Sem_Name_Array[4] == Scnd_Semester_Name)
								{
									if (First_Semester_Name == "FALL")
									{
										Course_Grade_Points[4] = Course_Grade;
									}
								}
							}
						}
						else if (Course_Code == "SL101")
						{
							if (First_Sem_Name_Array[5] == "" && Scnd_Sem_Name_Array[5] == "")
							{
								Course_Grade_Points[5] = Course_Grade;
								First_Sem_Name_Array[5] = First_Semester_Name;
								Scnd_Sem_Name_Array[5] = Scnd_Semester_Name;
								//cout << First_Semester_Name << endl;
							}
							else
							{
								if (Scnd_Sem_Name_Array[5] < Scnd_Semester_Name)
								{
									Course_Grade_Points[5] = Course_Grade;
								}
								else if (Scnd_Sem_Name_Array[5] == Scnd_Semester_Name)
								{
									if (First_Semester_Name == "FALL")
									{
										Course_Grade_Points[5] = Course_Grade;
									}
								}
							}
						}
						else if (Course_Code == "SS101")
						{
							if (First_Sem_Name_Array[6] == "" && Scnd_Sem_Name_Array[6] == "")
							{
								Course_Grade_Points[6] = Course_Grade;
								First_Sem_Name_Array[6] = First_Semester_Name;
								Scnd_Sem_Name_Array[6] = Scnd_Semester_Name;
								//cout << First_Semester_Name << endl;
							}
							else
							{
								if (Scnd_Sem_Name_Array[6] < Scnd_Semester_Name)
								{
									Course_Grade_Points[6] = Course_Grade;
								}
								else if (Scnd_Sem_Name_Array[6] == Scnd_Semester_Name)
								{
									if (First_Semester_Name == "FALL")
									{
										Course_Grade_Points[6] = Course_Grade;
									}
								}
							}
						}
						else if (Course_Code == "EE227")
						{
							if (First_Sem_Name_Array[7] == "" && Scnd_Sem_Name_Array[7] == "")
							{
								Course_Grade_Points[7] = Course_Grade;
								First_Sem_Name_Array[7] = First_Semester_Name;
								Scnd_Sem_Name_Array[7] = Scnd_Semester_Name;
								//cout << First_Semester_Name << endl;
							}
							else
							{
								if (Scnd_Sem_Name_Array[7] < Scnd_Semester_Name)
								{
									Course_Grade_Points[7] = Course_Grade;
								}
								else if (Scnd_Sem_Name_Array[7] == Scnd_Semester_Name)
								{
									if (First_Semester_Name == "FALL")
									{
										Course_Grade_Points[7] = Course_Grade;
									}
								}
							}
						}
						else if (Course_Code == "SS122")
						{
							if (First_Sem_Name_Array[8] == "" && Scnd_Sem_Name_Array[8] == "")
							{
								Course_Grade_Points[8] = Course_Grade;
								First_Sem_Name_Array[8] = First_Semester_Name;
								Scnd_Sem_Name_Array[8] = Scnd_Semester_Name;
								//cout << First_Semester_Name << endl;
							}
							else
							{
								if (Scnd_Sem_Name_Array[8] < Scnd_Semester_Name)
								{
									Course_Grade_Points[8] = Course_Grade;
								}
								else if (Scnd_Sem_Name_Array[8] == Scnd_Semester_Name)
								{
									if (First_Semester_Name == "FALL")
									{
										Course_Grade_Points[8] = Course_Grade;
									}
								}
							}
						}
						else if (Course_Code == "MT224")
						{
							if (First_Sem_Name_Array[9] == "" && Scnd_Sem_Name_Array[9] == "")
							{
								Course_Grade_Points[9] = Course_Grade;
								First_Sem_Name_Array[9] = First_Semester_Name;
								Scnd_Sem_Name_Array[9] = Scnd_Semester_Name;
								//cout << First_Semester_Name << endl;
							}
							else
							{
								if (Scnd_Sem_Name_Array[9] < Scnd_Semester_Name)
								{
									Course_Grade_Points[9] = Course_Grade;
								}
								else if (Scnd_Sem_Name_Array[9] == Scnd_Semester_Name)
								{
									if (First_Semester_Name == "FALL")
									{
										Course_Grade_Points[9] = Course_Grade;
									}
								}
							}
						}
						else if (Course_Code == "SS111")
						{
							if (First_Sem_Name_Array[10] == "" && Scnd_Sem_Name_Array[10] == "")
							{
								Course_Grade_Points[10] = Course_Grade;
								First_Sem_Name_Array[10] = First_Semester_Name;
								Scnd_Sem_Name_Array[10] = Scnd_Semester_Name;
								//cout << First_Semester_Name << endl;
							}
							else
							{
								if (Scnd_Sem_Name_Array[10] < Scnd_Semester_Name)
								{
									Course_Grade_Points[10] = Course_Grade;
								}
								else if (Scnd_Sem_Name_Array[10] == Scnd_Semester_Name)
								{
									if (First_Semester_Name == "FALL")
									{
										Course_Grade_Points[10] = Course_Grade;
									}
								}
							}
						}
						else if (Course_Code == "CS217")
						{
							if (First_Sem_Name_Array[11] == "" && Scnd_Sem_Name_Array[11] == "")
							{
								Course_Grade_Points[11] = Course_Grade;
								First_Sem_Name_Array[11] = First_Semester_Name;
								Scnd_Sem_Name_Array[11] = Scnd_Semester_Name;
								//cout << First_Semester_Name << endl;
							}
							else
							{
								if (Scnd_Sem_Name_Array[11] < Scnd_Semester_Name)
								{
									Course_Grade_Points[11] = Course_Grade;
								}
								else if (Scnd_Sem_Name_Array[11] == Scnd_Semester_Name)
								{
									if (First_Semester_Name == "FALL")
									{
										Course_Grade_Points[11] = Course_Grade;
									}
								}
							}
						}
						else if (Course_Code == "EL227")
						{
							if (First_Sem_Name_Array[12] == "" && Scnd_Sem_Name_Array[12] == "")
							{
								Course_Grade_Points[12] = Course_Grade;
								First_Sem_Name_Array[12] = First_Semester_Name;
								Scnd_Sem_Name_Array[12] = Scnd_Semester_Name;
								//cout << First_Semester_Name << endl;
							}
							else
							{
								if (Scnd_Sem_Name_Array[12] < Scnd_Semester_Name)
								{


									Course_Grade_Points[12] = Course_Grade;
								}
								else if (Scnd_Sem_Name_Array[12] == Scnd_Semester_Name)
								{
									if (First_Semester_Name == "FALL")
									{
										Course_Grade_Points[12] = Course_Grade;
									}
								}
							}
						}
						else if (Course_Code == "CL217")
						{
							if (First_Sem_Name_Array[13] == "" && Scnd_Sem_Name_Array[13] == "")
							{
								Course_Grade_Points[13] = Course_Grade;
								First_Sem_Name_Array[13] = First_Semester_Name;
								Scnd_Sem_Name_Array[13] = Scnd_Semester_Name;
								//cout << First_Semester_Name << endl;
							}
							else
							{
								if (Scnd_Sem_Name_Array[13] < Scnd_Semester_Name)
								{
									Course_Grade_Points[13] = Course_Grade;
								}
								else if (Scnd_Sem_Name_Array[13] == Scnd_Semester_Name)
								{
									if (First_Semester_Name == "FALL")
									{
										Course_Grade_Points[13] = Course_Grade;
									}
								}
							}
						}
						else if (Course_Code == "CS201")
						{
							if (First_Sem_Name_Array[14] == "" && Scnd_Sem_Name_Array[14] == "")
							{
								Course_Grade_Points[14] = Course_Grade;
								First_Sem_Name_Array[14] = First_Semester_Name;
								Scnd_Sem_Name_Array[14] = Scnd_Semester_Name;
								//cout << First_Semester_Name << endl;
							}
							else
							{
								if (Scnd_Sem_Name_Array[14] < Scnd_Semester_Name)
								{
									Course_Grade_Points[14] = Course_Grade;
								}
								else if (Scnd_Sem_Name_Array[14] == Scnd_Semester_Name)
								{
									if (First_Semester_Name == "FALL")
									{
										Course_Grade_Points[14] = Course_Grade;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	else
		cout << "cant open file" << endl;
	write_file.close();
}
//loading data into the array
double** Load_Data(string p)
{
	string path = p;
	//calling the preprocess function
	preprocess(path);
	//path = "C:\\Users\\Butt\\source\\repos\\TEST";
	//now reading preprocessed file in the folder and then returning the 2D array
	fstream Readpreprocessed;
	int comma_count = 0;
	string read_preprocs = "";
	int count = 0;
	int rows = 310;
	int col = 17;
	int a = -1, b = 0;
	cleanDataArray = new double* [rows];
	for (int i = 0; i < rows; i++)
	{
		cleanDataArray[i] = new double[col];
	}
	Readpreprocessed.open("preprocessed_Data.csv");
	if (Readpreprocessed.is_open())
	{
		while (!Readpreprocessed.eof())
		{
			comma_count = 0;
			string temp_val = "";
			read_preprocs = "";
			getline(Readpreprocessed, read_preprocs);
			if (count == 0)
			{
				count++;
				continue;
			}
			if (read_preprocs != "")
			{
				a++;
				b = 0;
				bool flag = true;
				int i = 0;
				temp_val = "";
				for (i = 0; i < read_preprocs.length(); i++)
				{
					if (read_preprocs[i] != ',')
					{
						temp_val += read_preprocs[i];
					}
					if (read_preprocs[i] == ',')
					{
						comma_count++;
						if (comma_count == 1)
						{
							temp_val = "";
							continue;
						}
						else
						{
							cleanDataArray[a][b] = stod(temp_val);
							temp_val = "";
							b++;
						}
					}
				}
			}
		}
	}
	else
		cout << "unable to open file" << endl;
	//now deleting the preprocessed file because data is successfuly loaded into an araray
	// whenever next time we need to load data new file will be made and it will not append the previous file
	// that is why deleting the previous file.
	Readpreprocessed.close();
	remove("preprocessed_Data.csv");
	return cleanDataArray;
}
double** Distance(double* predictedArray, int predictedArraySize, double** data, int dataRows, int dataCols)
{
	double** Distance_Return = new double* [dataRows];
	int col = 2;
	for (int i = 0; i < dataRows; i++)
	{
		Distance_Return[i] = new double[col];
	}
	for (int i = 0; i < dataRows; i++)
	{
		for (int j = 0; j < col; j++)
		{
			Distance_Return[i][j] = 0.0;
		}
	}
	double** Distance_cal = new double* [dataRows];
	for (int i = 0; i < dataRows; i++)
	{
		Distance_cal[i] = new double[dataCols];

	}
	//now finding the distance from respective grades
	for (int i = 0; i < dataRows; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			if (j == 0 || j == 1 || j == 4 || j == 5 || j == 6 || j == 7 || j == 8 || j == 9 || j == 10 || j == 12)
			{
				if (data[i][j] == -1)
				{
					Distance_Return[i][0] += abs(predictedArray[j] - (0 * data[i][j]));
				}
				else
					Distance_Return[i][0] += abs(predictedArray[j] - (data[i][j]));
			}
			else
			{
				if (data[i][j] == -1)
				{
					Distance_Return[i][0] += abs(predictedArray[j] - (0 * data[i][j]));
				}
				else
					Distance_Return[i][0] += (1.5 * abs(predictedArray[j] - data[i][j]));
			}
			//now placing data grade at the 2nd index of Distance Return array

		}
		Distance_Return[i][1] = data[i][16];
	}
	return Distance_Return;
}
// Return mean of all datapoint with the predicted datapoint along with Gardepoint in DS 


double** Sort_k_Dis(int k, double** distance, int distanceRows, int distanceCols)
{
	//now returning the descending order 
	for (int i = 0; i < distanceRows - 1; i++)
	{

		for (int j = 0; j < distanceRows - i - 1; j++)
		{
			//now swapping the results
			if (distance[j][0] > distance[j + 1][0])
			{
				//first swapping the distances
				double temp_distance = distance[j][0];
				distance[j][0] = distance[j + 1][0];
				distance[j + 1][0] = temp_distance;
				//now swapping the gpa
				double temp_gpa = distance[j][1];
				distance[j][1] = distance[j + 1][1];
				distance[j + 1][1] = temp_gpa;
			}
		}
	}
	//now declaring the dynamic array to return of the size of k
	double** sorted_distance_return = new double* [k];
	for (int i = 0; i < k; i++)
	{
		sorted_distance_return[i] = new double[2];
	}
	//now adding data into the array
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			sorted_distance_return[i][j] = distance[i][j];
		}
	}

	//now the arrary is sorted
	//no taking the k values from the distance array and returnin
	return sorted_distance_return;
}
// Return the 1st k sorted distance with Grade point in Ascending order 


string Grade_Frequency(double** sortedKList, int sortedKListRows, int sortedKListCols)
{
	//this count is for counting frequency of grade
	int count[11] = { 0 };
	for (int i = 0; i < sortedKListRows; i++)
	{
		if (sortedKList[i][1] == 4)
		{
			count[0] += 1;
		}
		if (sortedKList[i][1] == 3.67)
		{
			count[1] += 1;
		}
		if (sortedKList[i][1] == 3.33)
		{
			count[2] += 1;
		}
		if (sortedKList[i][1] == 3.0)
		{
			count[3] += 1;
		}
		if (sortedKList[i][1] == 2.67)
		{
			count[4] += 1;
		}
		if (sortedKList[i][1] == 2.33)
		{
			count[5] += 1;
		}
		if (sortedKList[i][1] == 2.0)
		{
			count[6] += 1;
		}
		if (sortedKList[i][1] == 1.67)
		{
			count[7] += 1;
		}
		if (sortedKList[i][1] == 1.33)
		{
			count[8] += 1;
		}
		if (sortedKList[i][1] == 1.0)
		{
			count[9] += 1;
		}
		if (sortedKList[i][1] == 0)
		{
			count[10] += 1;
		}
	}
	//nwo finding the max freq in count array
	double max = count[0];
	int index_count = 0;
	for (int i = 0; i < 12; i++)
	{
		if (max < count[i])
		{
			index_count = i;
			max = count[i];
		}
	}
	//now we have index and count of the number
	//now returning the grade 
	if (index_count == 0)
	{
		return "A";
	}
	if (index_count == 1)
	{
		return "A-";
	}
	if (index_count == 2)
	{
		return "B+";
	}if (index_count == 3)
	{
		return "B";
	}if (index_count == 4)
	{
		return "B-";
	}if (index_count == 5)
	{
		return "C+";
	}if (index_count == 6)
	{
		return "C";
	}if (index_count == 7)
	{
		return "C-";
	}if (index_count == 8)
	{
		return "D+";
	}if (index_count == 9)
	{
		return "D";
	}
	if (index_count == 10)
	{
		return "F";
	}
}
// Return the most frequent Grade in DS; You need to convert Grade point in Grade 


double* all_means(double** Data, int dataRows, int dataCols)// calculate and return mean of all datapoints
{
	//calculating all of the means of the students in data 
	//making an array to store means of all of the students
	double* allmeansArray = new double[dataRows];
	for (int i = 0; i < dataRows; i++)
	{
		allmeansArray[i] = 0;
	}
	//calculating the mean of all of the students
	for (int i = 0; i < dataRows; i++)
	{
		for (int j = 0; j < dataCols - 3; j++)//datacol-3 bcz required grades are 14
		{
			if (Data[i][j] == 4)
			{
				allmeansArray[i] += 13;
			}
			if (Data[i][j] == 3.67)
			{
				allmeansArray[i] += 11;
			}
			if (Data[i][j] == 3.33)
			{
				allmeansArray[i] += 10;
			}
			if (Data[i][j] == 3.0)
			{
				allmeansArray[i] += 9;
			}
			if (Data[i][j] == 2.67)
			{
				allmeansArray[i] += 8;
			}
			if (Data[i][j] == 2.33)
			{
				allmeansArray[i] += 7;
			}
			if (Data[i][j] == 2.0)
			{
				allmeansArray[i] += 6;
			}
			if (Data[i][j] == 1.67)
			{
				allmeansArray[i] += 5;
			}
			if (Data[i][j] == 1.33)
			{
				allmeansArray[i] += 4;
			}
			if (Data[i][j] == 1.0)
			{
				allmeansArray[i] += 3;
			}
			if (Data[i][j] == 0)
			{
				allmeansArray[i] += 1;
			}
			if (Data[i][j] == -1)
			{
				allmeansArray[i] += 0;
			}
		}
	}
	return allmeansArray;
}


double* initia_k_Means(int k, double* allMeans, int allMeansSize) // Return Mean of 1st 13 students and index of the array will be cluster number 
{	// i-e , value in 0th index will be considered as the mean of cluster 0 ,  
	// value in 1st index will be considered as the mean of cluster 1.
	double* initialKMeans = new double[k];
	for (int i = 0; i < k; i++)
	{
		initialKMeans[i] = 0;
	}
	for (int i = 0; i < k; i++)
	{
		initialKMeans[i] = allMeans[i];
	}
	return initialKMeans;
}


double* Dist(double* allMeans, int allMeansSize, double* clusterMeans, int clusterMeansSize)
{
	//now first of all calculating the distance of these clustern means from all means size
	double* distance_calc = new double[clusterMeansSize];

	for (int i = 0; i < clusterMeansSize; i++)
	{
		distance_calc[i] = 0;
	}
	//now the array to store the intermediate clusters
	double** intermediateClusters = new double* [clusterMeansSize];
	//making an array of index count of cluster that will help in last to find the grade of the students
	index_count_of_clusters = new double* [clusterMeansSize];
	col = abs(allMeansSize - clusterMeansSize);
	for (int i = 0; i < clusterMeansSize; i++)
	{
		intermediateClusters[i] = new double[col];
		index_count_of_clusters[i] = new double[col];
	}
	int* count_col = new int[clusterMeansSize];
	for (int i = 0; i < clusterMeansSize; i++)
		count_col[i] = 0;
	//now intializing teh arrays with zeros
	for (int i = 0; i < clusterMeansSize; i++)
	{
		for (int j = 0; j < col; j++)
		{
			intermediateClusters[i][j] = 0;
			index_count_of_clusters[i][j] = 0;
		}
	}


	for (int i = clusterMeansSize; i < allMeansSize; i++)
	{
		for (int j = 0; j < clusterMeansSize; j++)
		{
			distance_calc[j] = abs(allMeans[i] - clusterMeans[j]);
		}
		//now checking which have smaller distance and then moving it clusters
		double min = distance_calc[0];
		int index_count = 0;
		for (int j = 1; j < clusterMeansSize; j++)
		{
			if (min > distance_calc[j])
			{
				index_count = j;
				min = distance_calc[j];
			}
		}
		//now making the cluster in an an array whose mean will be find later
		for (int a = 0; a < col; a++)
		{
			if (intermediateClusters[index_count][a] == 0)
			{
				intermediateClusters[index_count][a] = allMeans[i];
				index_count_of_clusters[index_count][a] = i;

				count_col[index_count] += 1;
				break;
			}
			else
				continue;
		}
	}
	//now calculating the mean cluster from intermediate cluster array
	double* meansClusterArrayReturn = new double[clusterMeansSize];
	for (int i = 0; i < clusterMeansSize; i++)
	{
		meansClusterArrayReturn[i] = 0;
		count_col[i] += 1;
	}
	//now claculatin the cluster
	for (int i = 0; i < clusterMeansSize; i++)
		meansClusterArrayReturn[i] = clusterMeans[i];
	for (int i = 0; i < clusterMeansSize; i++)
	{
		for (int j = 0; j < col; j++)
		{
			meansClusterArrayReturn[i] += (intermediateClusters[i][j]);
		}
		meansClusterArrayReturn[i] /= count_col[i];
	}

	return meansClusterArrayReturn;
}
// Find the distance between mean of all datapoint and the mean of each cluster.  
// Assign closest cluster to each datapoint
// calculate new mean against each cluster 
// Return Updated Mean 



bool  Accuracy(double* oldClusterMeans, int oldClusterMeansSize, double* newClusterMeans, int newClusterMeansSize)
{
	bool flag = false;
	if (oldClusterMeansSize != newClusterMeansSize)
	{
		return false;
	}
	else {
		for (int i = 0; i < oldClusterMeansSize; i++)
		{
			if (oldClusterMeans[i] - newClusterMeans[i] <= 0.001)
			{
				flag = false;
			}
			else
			{
				return false;
			}
		}
	}
	if (flag == false)
	{
		return true;
	}
}
// return True if both means are same otherwise return false 
string Prediction(double newData, double* meansOfClustors, int meansOfClustorsSize)
{
	double* distance_calc = new double[meansOfClustorsSize];
	for (int i = 0; i < meansOfClustorsSize; i++)
	{
		distance_calc[i] = 0;
	}
	//now finding the distance
	for (int i = 0; i < meansOfClustorsSize; i++) {
		distance_calc[i] = abs(newData - meansOfClustors[i]);
	}
	//now finding the minimum distance 
	double min = distance_calc[0];
	int min_index = 0;
	for (int i = 1; i < meansOfClustorsSize; i++)
	{
		if (min > distance_calc[i])
		{
			min = distance_calc[i];
			min_index = i;
		}
	}
	//now we have teh minimum distance
	//now we have the index of the minimum distance and now we can searcch in index count cluster array
	int grad_retrive = 0;
	//an array to store data structure grades
	double* store_Data_Grade = new double[col];
	for (int i = 0; i < col; i++)
		store_Data_Grade[i] = 0.0;
	for (int i = 0; i < col; i++)
	{
		if (index_count_of_clusters[min_index][i] != 0)
		{
			grad_retrive = index_count_of_clusters[min_index][i];
			store_Data_Grade[i] = cleanDataArray[grad_retrive][16];
		}
		else
			continue;
	}
	//now finding the max repeated course
	int count[11] = { 0 };
	for (int i = 0; i < col; i++)
	{
		if (store_Data_Grade[i] == 4)
		{
			count[0] += 1;
		}
		if (store_Data_Grade[i] == 3.67)
		{
			count[1] += 1;
		}
		if (store_Data_Grade[i] == 3.33)
		{
			count[2] += 1;
		}
		if (store_Data_Grade[i] == 3.0)
		{
			count[3] += 1;
		}
		if (store_Data_Grade[i] == 2.67)
		{
			count[4] += 1;
		}
		if (store_Data_Grade[i] == 2.33)
		{
			count[5] += 1;
		}
		if (store_Data_Grade[i] == 2.0)
		{
			count[6] += 1;
		}
		if (store_Data_Grade[i] == 1.67)
		{
			count[7] += 1;
		}
		if (store_Data_Grade[i] == 1.33)
		{
			count[8] += 1;
		}
		if (store_Data_Grade[i] == 1.0)
		{
			count[9] += 1;
		}
		if (store_Data_Grade[i] == 0)
		{
			count[10] += 1;
		}
	}
	//nwo finding the max freq in count array
	double max = count[0];
	int index_count = 0;
	for (int i = 0; i < 12; i++)
	{
		if (max < count[i])
		{
			index_count = i;
			max = count[i];
		}
	}
	//now calculating the grade
	if (index_count == 0)
	{
		return "A";
	}
	if (index_count == 1)
	{
		return "A-";
	}
	if (index_count == 2)
	{
		return "B+";
	}if (index_count == 3)
	{
		return "B";
	}if (index_count == 4)
	{
		return "B-";
	}if (index_count == 5)
	{
		return "C+";
	}if (index_count == 6)
	{
		return "C";
	}if (index_count == 7)
	{
		return "C-";
	}if (index_count == 8)
	{
		return "D+";
	}if (index_count == 9)
	{
		return "D";
	}
	if (index_count == 10)
	{
		return "F";
	}
}
// Calculate the distance of upcoming datapoint with the whole cluster means
//  and convert the index of closest cluster mean into Grade and return it.