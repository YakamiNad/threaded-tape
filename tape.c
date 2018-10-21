#include "tape.h"
#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<stdint.h>
pthread_t th[10];
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
int arg=0;
int id=0;
int ss=0;
char buf[30];
FILE *fp[10];
int numberofbytes;
int cs[11];
 FILE *org;
int count=0;
int cc=0;
void* tape_reader(void* args) {
    pthread_mutex_lock(&mutex);
	numberofbytes=*(int*) args;
        
    	fseek(org,0,SEEK_END);
   int fl= ftell(org);
    uint8_t rd[fl];
    // printf("%d",fl);
    rewind(org);
    fread(rd,fl,1,org);
    // printf("%d\n",numberofbytes);
    if(numberofbytes>=0){ 
        // printf("%d\n",fl);
 // printf("%d\n",cs[count]);   
            // for(int k=0;k<arg;k++){
                if(cs[count]>0){
                    int a=cs[count];
                    if(numberofbytes<=(fl-a)){ 
               fwrite(&rd[a],numberofbytes,1,fp[count]); 
                    }
                    else if(numberofbytes>(fl-a)){
                       for(int i=0;i<(fl-a);i++){
                        
               fwrite(&rd[a+i],1,1,fp[count]);//write the rd to fp[k];
                    }
                        for(int i=0;i<(fl-numberofbytes);i++){
                             fwrite(&rd[i],1,1,fp[count]);
                        }
                    }

            }
        if(cs[count]==0){
            for(int i=0;i<numberofbytes;i++){ 
            fwrite(&rd[i],1,1,fp[count]);
        }
        }
                if(cs[count]<0){
                    int a=cs[count];
                    int b=a*(-1);
                    if(numberofbytes<=b){ 
                             fwrite(&rd[a+fl],numberofbytes,1,fp[count]);
    
                    }
                    if(numberofbytes>b){
                        fwrite(&rd[a+fl],b,1,fp[count]);
                        fwrite(&rd[0],numberofbytes-b,1,fp[count]);
                    }
                    
                    //  printf("count<0\n");
                    // printf("cursor: %d\n",cs[count]+fl-1);
                        
               //       fseek(org,(cs[count]+fl-1),0);//move the cursor to the given file
               // fread(rd,numberofbytes,1,org);//try to read index numbers starting from the cursor
               // fwrite(rd,numberofbytes,1,fp[count]);//write the rd to fp[k];
               // printf("%s\n",rd);
                // printf("%d\n",count);
               //      for(int i=0;i<numberofbytes;i++){ 
               // fwrite(&rd[a+fl+i],1,1,fp[count]);//write the rd to fp[k];
               //      }
               //  }
                }
            }
    
    
    else{
        if(cs[count]>0){ 
            int a=cs[count];
            // int b=numberofbytes*(-1);
            for(int i=(a-1);i>=(numberofbytes+a);i--){
                fwrite(&rd[i],1,1,fp[count]);
            }
          // printf("read minus\n");
                // printf("fff");
//                fseek(org,cs[count]+numberofbytes+fl,SEEK_SET);//move the cursor to the given file
//                fread(rd,numberofbytes,1,org);
//                     // printf("%s\n",rd);
            
//                fwrite(rd,numberofbytes,1,fp[count]);//write the rd to fp[k];

                }
        //  if(cs[count]==0){
        //     fwrite(&rd[0],numberofbytes,1,fp[count]);
        // }
        if(cs[count]<=0){
            int a=cs[count];
            int b=numberofbytes*(-1);
            // int c=cs[count]*(-1);
            
            for(int i=a+fl-1;i>=(fl+a-b);i--){
               fwrite(&rd[i],1,1,fp[count]);
            }
            
        }
    }
              // if(cs[k]<0){
              //     fseek(org,cs[k]+numberofbytes+fl,SEEK_SET);//move the cursor to the given file
              //  fread(rd,numberofbytes,1,org);
              //       // printf("%s\n",rd);
              //  fwrite(rd,numberofbytes,1,fp[k]);//wr 
              // }
 cs[count]=cs[count]+numberofbytes;
 count++;
    pthread_mutex_unlock(&mutex);
      return NULL;
}


int main(int argc,char** argv) {
    // fflush(stdin);
	if(argc==1){
        printf("Tape Not Inserted\n");
        return 0;
    }
    if(fopen(argv[1],"rb")==NULL){
        printf("Cannot Read Tape\n");
        return 0;
    }
   org=fopen(argv[1],"rb");
    while(1){
        char input[30];
        int index;
        char buffer[30];
        fgets(buf,30,stdin);
		sscanf(buf,"%s %d",input,&index);
        
         if(strcmp(buf,"QUIT\n")==0){ 
             for(int i=0;i<id;i++){
                 fclose(fp[i]);
             }
             break;
         }
        if(strcmp(input,"HEAD")==0){
              if(index>=0){ 
           printf("HEAD %d at +%d\n",id+1,index);
                  printf("\n");
        }
              if(index<0){ 
                printf("HEAD %d at %d\n",id+1,index);
                  printf("\n");
            }
            cs[id]=index;//store the cursor 
            id++;//increase the count
            sprintf(buffer, "head%d", (arg+1));//create the file head[i]
            fp[arg]=fopen(buffer,"wb");
            // pthread_create(&th[arg],NULL,tape_reader,&index);//create the thread when reciving
            //wait for the thread to be finished
            arg++;//increase the arg for next thread and file creation
        
        }
        if(strcmp(input,"READ")==0){
            for(int i=0;i<id;i++){
                 pthread_create(&th[i],NULL,tape_reader,&index);
                 // pthread_join(th[count+i],NULL);
                //create the number of threads of the times HEAD been input      
            }
            for(int i=0;i<(id);i++){
                 pthread_join(th[i],NULL);
            }
//             for(int i=0;i<id;i++){
//                 cs[i]=cs[i]+index;
//             }
               
            //head 0
            //read 1
            //head 1
            //head 2
            //read 2
            count=0;
             printf("Finished Reading\n");
            printf("\n");
            // fclose(org);
        }
        continue;
       
    }
	return 0;
}
