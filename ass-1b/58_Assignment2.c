/* Name : Somnath Mishra
 * Roll No: 002211001058
 * Assignment No -1b
 * Date - 01.08.2024
 */


#include<stdlib.h>
#include<stdio.h>

int main(){
	const char *name="USER";
	const char *env_p=getenv(name);
	if(env_p){
		printf("Your %s is %s\n",name,env_p);
	}
	env_p=getenv("HOME");
	printf("Your %s is %s\n","HOME",env_p);
	env_p=getenv("HOST");
	printf("Your %s is %s\n","HOST",env_p);
	env_p=getenv("ARCH");
	printf("Your %s is %s\n","ARCH",env_p);
	env_p=getenv("DISPLAY");
	printf("Your %s is %s\n","DISPLAY",env_p);
	env_p=getenv("PRINTER");
	printf("Your %s is %s\n","PRINTER",env_p);
	env_p=getenv("PATH");
	printf("Your %s is %s\n","PATH",env_p);
	
	//seting env variable
	setenv("TEST","SETTING A ENV VARIABLE",1);
	printf("Your %s is %s\n","TEST",getenv("TEST"));
	
	setenv("ENV_VARIABLE","Value of env Varialbe",1);
	printf("Your %s is %s\n","ENV_VARIABLE",getenv("ENV_VARIABLE"));

	return 0;
}

