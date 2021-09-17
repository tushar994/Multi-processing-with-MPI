Team no - 2
Tushar Jain - 2019101091
Sabyasachi Mukhopadhyay - 2021801003


These were done using the MPI library. Both questions use 4 processors.


## To Run

```shell
$ module load hpcx-2.7.0/hpcx-ompi
$ mpic++ Q3.cpp
$ mpirun -np 4 -mca coll ^hcoll --use-hwthread-cpus ./a.out

```

