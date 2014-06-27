//
//  mpi.h
//  TaskScheduller1.0
//
//  Created by Maxim Chetrusca on 11/8/13.
//  Copyright (c) 2013 Maxim Chetrusca. All rights reserved.
//

#ifndef TaskScheduller1_0_mpi_h
#define TaskScheduller1_0_mpi_h

//Dummy typedefs
typedef int MPI_Status;
typedef int MPI_Comm;
typedef int MPI_Datatype;

//Dummy defines:
#define MPI_COMM_WORLD 1
#define MPI_CHAR 1
#define MPI_ANY_SOURCE 1
#define MPI_ANY_TAG 1
#define MPI_INT 1
#define MPI_PACKED 1
#define MPI_SHORT 1
#define MPI_UNSIGNED 1

/* start up MPI */
int MPI_Init(int *argc,char ***argv);

/* find out process rank */
int MPI_Comm_rank(MPI_Comm comm, int *rank);

/* find out number of processes */
int MPI_Comm_size(MPI_Comm comm, int *size);

int MPI_Send(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);

int MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status);

int MPI_Iprobe(int source, int tag, MPI_Comm comm, int *flag, MPI_Status *status);

int MPI_Finalize();

int MPI_Pack(void *inbuf,
             int incount,
             MPI_Datatype datatype,
             void *outbuf,
             int outcount,
             int *position,
             MPI_Comm comm);

int MPI_Unpack(void *inbuf, int insize, int *position,
               void *outbuf, int outcount, MPI_Datatype datatype,
               MPI_Comm comm);

//int MPI_Isend(void *buf, int count, MPI_Datatype datatype, int dest, int tag,
//              MPI_Comm comm, MPI_Request *request);


#endif
