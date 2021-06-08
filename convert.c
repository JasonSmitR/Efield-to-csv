//This is a hacked together version to extract data from a 2 channel stream
//It may be best to refactor this and abstract it to work for n streams
//6 getlines should replace fseek
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAGICNUMBER 4.884
//#define SCALE2 1/4.444

int main(int argc, char** argv) {
    FILE *fp;
    int16_t data;
    float val1;
    float val2;
    float channel1gain;
    float channel2gain;
    float channel3gain;
    float channel4gain;
    char datetime[21]= "";
    fp = fopen(argv[1], "rb")

    //get the file information from the first input and assume the same throughout
    fseek(fp, 96, SEEK_SET);     
    fread(&channel1gain,6,1,fp); //get channel 1 sen 
    fseek(fp, 148, SEEK_SET);
    fread(&channel2gain,6,1,fp); //get channel 2 sen
    fseek(fp, 206, SEEK_SET);
    fread(&channel3gain,6,1,fp); //get channel 3 sen
    fseek(fp, 264, SEEK_SET);
    fread(&channel4gain,6,1,fp); //get channel 4 sen 

    fseek(fp, 279, SEEK_SET);
    fread(&datetime,20,1,fp);

    printf ("Chan 1: %f \n Chan2: %f \n Chan3: %f \n Chan3: %f \n date: %s", channel1gain, channel2gain, channel3gain, channel4gain, datetime)



    /*FILE *f1ptr = fopen("channel1.txt", "w");
    FILE *f2ptr = fopen("channel2.txt", "w");
    if (f1ptr == NULL && f2ptr == NULL ) { 
        printf("Could not open file"); 
        return 0; 
    }
    if(argc >1){ //there are inputs to the file                              
      for(int i = 1; i < argc;i++) {
	      int a = argc - 1;
        printf("Processing input %d of %d \n", i,a);
        fp = fopen(argv[i], "rb");

        fseek(fp, 300, SEEK_SET);
        //char line[128];
        //for(int i=0;i<2;i++){
	//	fgets(line, 128, fp); //getline and discard 
	//	//getline(&line, &size, fp)
	//}
        while (!feof(fp)){
            fread(&data, sizeof(data), 1, fp);
            val1 = data * SCALE1;
	          //not good but it will work for now
	          fread(&data, sizeof(data), 1, fp);
	          val2 = data * SCALE2; //wasteful but for multiple input it is needed to allow for the removal of the last lines of each file
	          if(!feof(fp)){ // if last line ignore: hacky way to leave out last line
		          fprintf(f1ptr,"%f\n", val1);
		          fprintf(f2ptr, "%f\n",val2);
	          }
        }
      }
    }
    fclose(f1ptr);
    fclose(f2ptr);
    */    
}
