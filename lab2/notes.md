pid = fork()

if(pid == 0){
    //Child work
    // return -> exit
}

else{
    //parent work
    // return -> exit
}


// Daca nu avem return sau exit codul de aici va fi executat de parinte si copil




pid = fork()

if(pid == 0){
    //Child work
    //Exec
     //getpid(), getppid()
    // return -> exit

}

else{
    //parent work

    // return -> exit

}






## EXEC:

pid = fork()

if(pid == 0){
    //Child work
    //Exec
        -> execl, execv, execle, execve, execlp, execvpe, execpv

        -> execl("program de rulat", "argo0(numele proc)", "arg1", "arg2", ... "null")
        -> execv(program, vec_argumente[arg0, arg1, ..., NULL])

        -> execle, execlve
            (similar cu celelalte dar cu enviorment)
            -> enviorment, un vector null terminated

        -> execlp, execvp, la fel dar cauta si in path
        -> execvpe
            //Search in path + env



         
     //getpid(), getppid()
    // return -> exit

}

else{
    //Wait - astept terminarea executiei copilului

    //parent work

    // return -> exit

}