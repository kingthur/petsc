#if !defined (__MPIUNIFDEF_H)
#define __MPIUNIFDEF_H

#define MPI_Init                  PETSC_MPI_INIT
#define MPI_Finalize              PETSC_MPI_FINALIZE
#define MPI_Comm_size             PETSC_MPI_COMM_SIZE
#define MPI_Comm_rank             PETSC_MPI_COMM_RANK
#define MPI_Abort                 PETSC_MPI_ABORT
#define MPI_Reduce                PETSC_MPI_REDUCE
#define MPI_Allreduce             PETSC_MPI_ALLREDUCE
#define MPI_Barrier               PETSC_MPI_BARRIER
#define MPI_Bcast                 PETSC_MPI_BCAST
#define MPI_Gather                PETSC_MPI_GATHER
#define MPI_Allgather             PETSC_MPI_ALLGATHER
#define MPI_Comm_split            PETSC_MPI_COMM_SPLIT
#define MPI_Scan                  PETSC_MPI_SCAN
#define MPI_Send                  PETSC_MPI_SEND
#define MPI_Recv                  PETSC_MPI_RECV
#define MPI_Reduce_scatter        PETSC_MPI_REDUCE_SCATTER
#define MPI_Irecv                 PETSC_MPI_IRECV
#define MPI_Isend                 PETSC_MPI_ISEND
#define MPI_Sendrecv              PETSC_MPI_SENDRECV
#define MPI_Test                  PETSC_MPI_TEST
#define MPI_Waitall               PETSC_MPI_WAITALL
#define MPI_Waitany               PETSC_MPI_WAITANY
#define MPI_Allgatherv            PETSC_MPI_ALLGATHERV
#define MPI_Alltoallv             PETSC_MPI_ALLTOALLV
#define MPI_Comm_create           PETSC_MPI_COMM_CREATE
#define MPI_Address               PETSC_MPI_ADDRESS
#define MPI_Pack                  PETSC_MPI_PACK
#define MPI_Unpack                PETSC_MPI_UNPACK
#define MPI_Pack_size             PETSC_MPI_PACK_SIZE
#define MPI_Type_struct           PETSC_MPI_TYPE_STRUCT
#define MPI_Type_commit           PETSC_MPI_TYPE_COMMIT
#define MPI_Wtime                 PETSC_MPI_WTIME
#define MPI_Cancel                PETSC_MPI_CANCEL
#define MPI_Comm_dup              PETSC_MPI_COMM_DUP
#define MPI_Comm_free             PETSC_MPI_COMM_FREE
#define MPI_Get_count             PETSC_MPI_GET_COUNT
#define MPI_Get_processor_name    PETSC_MPI_GET_PROCESSOR_NAME
#define MPI_Initialized           PETSC_MPI_INITIALIZED
#define MPI_Iprobe                PETSC_MPI_IPROBE
#define MPI_Probe                 PETSC_MPI_PROBE
#define MPI_Request_free          PETSC_MPI_REQUEST_FREE
#define MPI_Ssend                 PETSC_MPI_SSEND
#define MPI_Wait                  PETSC_MPI_WAIT
#define MPI_Comm_group            PETSC_MPI_COMM_GROUP
#define MPI_Exscan                PETSC_MPI_EXSCAN

#define MPI_INIT                  PETSC_MPI_INIT
#define MPI_FINALIZE              PETSC_MPI_FINALIZE
#define MPI_COMM_SIZE             PETSC_MPI_COMM_SIZE
#define MPI_COMM_RANK             PETSC_MPI_COMM_RANK
#define MPI_ABORT                 PETSC_MPI_ABORT
#define MPI_REDUCE                PETSC_MPI_REDUCE
#define MPI_ALLREDUCE             PETSC_MPI_ALLREDUCE
#define MPI_BARRIER               PETSC_MPI_BARRIER
#define MPI_BCAST                 PETSC_MPI_BCAST
#define MPI_GATHER                PETSC_MPI_GATHER
#define MPI_ALLGATHER             PETSC_MPI_ALLGATHER
#define MPI_COMM_SPLIT            PETSC_MPI_COMM_SPLIT
#define MPI_SCAN                  PETSC_MPI_SCAN
#define MPI_SEND                  PETSC_MPI_SEND
#define MPI_RECV                  PETSC_MPI_RECV
#define MPI_REDUCE_SCATTER        PETSC_MPI_REDUCE_SCATTER
#define MPI_IRECV                 PETSC_MPI_IRECV
#define MPI_ISEND                 PETSC_MPI_ISEND
#define MPI_SENDRECV              PETSC_MPI_SENDRECV
#define MPI_TEST                  PETSC_MPI_TEST
#define MPI_WAITALL               PETSC_MPI_WAITALL
#define MPI_WAITANY               PETSC_MPI_WAITANY
#define MPI_ALLGATHERV            PETSC_MPI_ALLGATHERV
#define MPI_ALLTOALLV             PETSC_MPI_ALLTOALLV
#define MPI_COMM_CREATE           PETSC_MPI_COMM_CREATE
#define MPI_ADDRESS               PETSC_MPI_ADDRESS
#define MPI_PACK                  PETSC_MPI_PACK
#define MPI_UNPACK                PETSC_MPI_UNPACK
#define MPI_PACK_SIZE             PETSC_MPI_PACK_SIZE
#define MPI_TYPE_STRUCT           PETSC_MPI_TYPE_STRUCT
#define MPI_TYPE_COMMIT           PETSC_MPI_TYPE_COMMIT
#define MPI_WTIME                 PETSC_MPI_WTIME
#define MPI_CANCEL                PETSC_MPI_CANCEL
#define MPI_COMM_DUP              PETSC_MPI_COMM_DUP
#define MPI_COMM_FREE             PETSC_MPI_COMM_FREE
#define MPI_GET_COUNT             PETSC_MPI_GET_COUNT
#define MPI_GET_PROCESSOR_NAME    PETSC_MPI_GET_PROCESSOR_NAME
#define MPI_INITIALIZED           PETSC_MPI_INITIALIZED
#define MPI_IPROBE                PETSC_MPI_IPROBE
#define MPI_PROBE                 PETSC_MPI_PROBE
#define MPI_REQUEST_FREE          PETSC_MPI_REQUEST_FREE
#define MPI_SSEND                 PETSC_MPI_SSEND
#define MPI_WAIT                  PETSC_MPI_WAIT
#define MPI_COMM_GROUP            PETSC_MPI_COMM_GROUP
#define MPI_EXSCAN                PETSC_MPI_EXSCAN

#define mpi_init                  PETSC_MPI_INIT
#define mpi_finalize              PETSC_MPI_FINALIZE
#define mpi_comm_size             PETSC_MPI_COMM_SIZE
#define mpi_comm_rank             PETSC_MPI_COMM_RANK
#define mpi_abort                 PETSC_MPI_ABORT
#define mpi_reduce                PETSC_MPI_REDUCE
#define mpi_allreduce             PETSC_MPI_ALLREDUCE
#define mpi_barrier               PETSC_MPI_BARRIER
#define mpi_bcast                 PETSC_MPI_BCAST
#define mpi_gather                PETSC_MPI_GATHER
#define mpi_allgather             PETSC_MPI_ALLGATHER
#define mpi_comm_split            PETSC_MPI_COMM_SPLIT
#define mpi_scan                  PETSC_MPI_SCAN
#define mpi_send                  PETSC_MPI_SEND
#define mpi_recv                  PETSC_MPI_RECV
#define mpi_reduce_scatter        PETSC_MPI_REDUCE_SCATTER
#define mpi_irecv                 PETSC_MPI_IRECV
#define mpi_isend                 PETSC_MPI_ISEND
#define mpi_sendrecv              PETSC_MPI_SENDRECV
#define mpi_test                  PETSC_MPI_TEST
#define mpi_waitall               PETSC_MPI_WAITALL
#define mpi_waitany               PETSC_MPI_WAITANY
#define mpi_allgatherv            PETSC_MPI_ALLGATHERV
#define mpi_alltoallv             PETSC_MPI_ALLTOALLV
#define mpi_comm_create           PETSC_MPI_COMM_CREATE
#define mpi_address               PETSC_MPI_ADDRESS
#define mpi_pack                  PETSC_MPI_PACK
#define mpi_unpack                PETSC_MPI_UNPACK
#define mpi_pack_size             PETSC_MPI_PACK_SIZE
#define mpi_type_struct           PETSC_MPI_TYPE_STRUCT
#define mpi_type_commit           PETSC_MPI_TYPE_COMMIT
#define mpi_wtime                 PETSC_MPI_WTIME
#define mpi_cancel                PETSC_MPI_CANCEL
#define mpi_comm_dup              PETSC_MPI_COMM_DUP
#define mpi_comm_free             PETSC_MPI_COMM_FREE
#define mpi_get_count             PETSC_MPI_GET_COUNT
#define mpi_get_processor_name    PETSC_MPI_GET_PROCESSOR_NAME
#define mpi_initialized           PETSC_MPI_INITIALIZED
#define mpi_iprobe                PETSC_MPI_IPROBE
#define mpi_probe                 PETSC_MPI_PROBE
#define mpi_request_free          PETSC_MPI_REQUEST_FREE
#define mpi_ssend                 PETSC_MPI_SSEND
#define mpi_wait                  PETSC_MPI_WAIT
#define mpi_comm_group            PETSC_MPI_COMM_GROUP
#define mpi_exscan                PETSC_MPI_EXSCAN

#endif
