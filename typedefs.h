
typedef unsigned __int8 u8;
typedef unsigned __int16 u16;
typedef unsigned __int32 u32;
typedef unsigned __int64 u64;
typedef __int8 s8;
typedef __int16 s16;
typedef __int32 s32;
typedef __int64 s64;
typedef __int32 size_t;


typedef void * (*SifRpcFunc_t)(int fno, void *buffer, int length);
typedef void (*SifRpcEndFunc_t)(void *end_param);

typedef struct t_SifRpcServerData {
  int sid;

  SifRpcFunc_t func;
  void  *buff;
  int size;

  SifRpcFunc_t cfunc;
  void  *cbuff;
  int size2;

  struct t_SifRpcClientData *client;
  void  *pkt_addr;
  int rpc_number;

  void  *receive;
  int rsize;
  int rmode;
  int rid;

  struct t_SifRpcServerData *link;
  struct t_SifRpcServerData *next;
  struct t_SifRpcDataQueue *base;
} SifRpcServerData_t;

typedef struct t_SifRpcHeader {
  void  *pkt_addr;
  u32 rpc_id;
  int sema_id;
  u32 mode;
} SifRpcHeader_t;

typedef struct t_SifRpcClientData {
  struct t_SifRpcHeader hdr;
  u32 command;
  void  *buff;
  void  *cbuff;
  SifRpcEndFunc_t end_function;
  void  *end_param;
  struct t_SifRpcServerData *server;
} SifRpcClientData_t;

typedef struct t_SifRpcReceiveData {
  struct t_SifRpcHeader hdr;
  void  *src;
  void  *dest;
  int size;
} SifRpcReceiveData_t;

typedef struct t_SifRpcDataQueue {
  int thread_id;
  int active;
  struct t_SifRpcServerData *link;
  struct t_SifRpcServerData *start;
  struct t_SifRpcServerData *end;
  struct t_SifRpcDataQueue *next;
} SifRpcDataQueue_t;



typedef struct {
  unsigned int mode;
  unsigned int attr;
  unsigned int size;
  unsigned char ctime[8];
  unsigned char atime[8];
  unsigned char mtime[8];
  unsigned int hisize;
} io_stat_t;

typedef struct {
  io_stat_t stat;
  char name[256];
  unsigned int unknown;
} io_dirent_t;


typedef struct {
  unsigned int  mode;
  unsigned int  attr;
  unsigned int  size;
  unsigned char ctime[8];
  unsigned char atime[8];
  unsigned char mtime[8];
  unsigned int  hisize;
  
  unsigned int  private_0;
  unsigned int  private_1;
  unsigned int  private_2;
  unsigned int  private_3;
  unsigned int  private_4;
  
  unsigned int  private_5;
} iox_stat_t;

typedef struct {
  iox_stat_t  stat;
  char    name[256];
  unsigned int  unknown;
} iox_dirent_t;



typedef struct _iop_file {
  
  int mode;   
  
  int unit;   
  
  struct _iop_device *device; 
  
  void  *privdata;  
} iop_file_t;

typedef struct _iop_device {
  const char *name;
  unsigned int type;
  
  unsigned int version;
  const char *desc;
  struct _iop_device_ops *ops;
} iop_device_t;

typedef struct _iop_device_ops {
#if 1
  int (*init)(iop_device_t *);
  int (*deinit)(iop_device_t *);
  int (*format)(iop_file_t *);
  int (*open)(iop_file_t *, const char *, int);
  int (*close)(iop_file_t *);
  int (*read)(iop_file_t *, void *, int);
  int (*write)(iop_file_t *, void *, int);
  int (*lseek)(iop_file_t *, int, int);
  int (*ioctl)(iop_file_t *, int, void *);
  int (*remove)(iop_file_t *, const char *);
  int (*mkdir)(iop_file_t *, const char *);
  int (*rmdir)(iop_file_t *, const char *);
  int (*dopen)(iop_file_t *, const char *);
  int (*dclose)(iop_file_t *);
  int (*dread)(iop_file_t *, io_dirent_t *);
  int (*getstat)(iop_file_t *, const char *, io_stat_t *);
  int (*chstat)(iop_file_t *, const char *, io_stat_t *, unsigned int);
#else
  int (*init)(iop_device_t *);
  int (*deinit)(iop_device_t *);
  int (*format)(iop_file_t *, const char *, const char *, void *, int);
  int (*open)(iop_file_t *, const char *, int, int);
  int (*close)(iop_file_t *);
  int (*read)(iop_file_t *, void *, int);
  int (*write)(iop_file_t *, void *, int);
  int (*lseek)(iop_file_t *, int, int);
  int (*ioctl)(iop_file_t *, int, void *);
  int (*remove)(iop_file_t *, const char *);
  int (*mkdir)(iop_file_t *, const char *, int);
  int (*rmdir)(iop_file_t *, const char *);
  int (*dopen)(iop_file_t *, const char *);
  int (*dclose)(iop_file_t *);
  int (*dread)(iop_file_t *, iox_dirent_t *);
  int (*getstat)(iop_file_t *, const char *, iox_stat_t *);
  int (*chstat)(iop_file_t *, const char *, iox_stat_t *, unsigned int);

  
  int (*rename)(iop_file_t *, const char *, const char *);
  int (*chdir)(iop_file_t *, const char *);
  int (*sync)(iop_file_t *, const char *, int);
  int (*mount)(iop_file_t *, const char *, const char *, int, void *, int);
  int (*umount)(iop_file_t *, const char *);
  s64 (*lseek64)(iop_file_t *, s64, int);
  int (*devctl)(iop_file_t *, const char *, int, void *, unsigned int, void *, unsigned int);
  int (*symlink)(iop_file_t *, const char *, const char *);
  int (*readlink)(iop_file_t *, const char *, char *, unsigned int);
  int (*ioctl2)(iop_file_t *, int, void *, unsigned int, void *, unsigned int);
#endif
} iop_device_ops_t;


typedef struct {
  u32 attr;
  u32 option;
  u32 bits;
} iop_event_t;

typedef struct {
  
  u32 attr;
  
  u32 option;
  
  u32 initBits;
  
  u32 currBits;
  
  int numThreads;
  int reserved1;
  int reserved2;
} iop_event_info_t;


typedef struct _iop_fpl_param {
  unsigned int attr;
  unsigned int option;
  int block_size;
  int blocks;
} iop_fpl_param;

typedef struct _iop_fpl_info {
  unsigned int attr;
  unsigned int option;
  int blockSize;
  int numBlocks;
  int freeBlocks;
  int numWaitThreads;
  int reserved[4];
} iop_fpl_info_t;


typedef struct {
  unsigned int attr;
  unsigned int option;
} iop_mbx_t;


typedef struct {
  u32 attr;
  u32 option;
  int initial;
  int max;
} iop_sema_t;

typedef struct {
  u32 attr;
  u32 option;
  int initial;
  int max;
  int current;
  int numWaitThreads;
  int reserved[2];
} iop_sema_info_t;



typedef struct _iop_vpl_param {
  unsigned int attr;
  unsigned int option;
  int size;
} iop_vpl_param;

typedef struct _iop_vpl_info {
  unsigned int attr;
  unsigned int option;
  int size;
  int freeSize;
  int numWaitThreads;
  int reserved[3];
} iop_vpl_info_t;


typedef struct _iop_thread {
  u32 attr;
  u32 option;
  void  (*thread)(void *);
  u32 stacksize;
  u32 priority;
} iop_thread_t;


typedef struct _iop_thread_status {
  unsigned int attr;
  unsigned int option;
  int status;
  void *entry;
  void *stack;
  int stackSize;
  void *gpReg;
  int initPriority;
  int currentPriority;
  int waitType;
  int waitId;
  int wakeupCount;
  
  long int *regContext; 
  unsigned int reserved[4];
} iop_thread_info_t;

typedef struct _iop_sys_clock {
  u32 lo, hi;
} iop_sys_clock_t;

typedef struct _iop_thread_run_status {
  int status;
  int currentPriority;
  int waitType;
  int waitId;
  int wakeupCount;
  long int *regContext;
  iop_sys_clock_t runClocks;
  unsigned int intrPreemptCount;
  unsigned int threadPreemptCount;
  unsigned int releaseCount;
} iop_thread_run_status_t;

typedef struct _iop_sys_status {
  unsigned int status;
  int systemLowTimerWidth;
  iop_sys_clock_t idleClocks;
  iop_sys_clock_t kernelClocks;
  unsigned int comesOutOfIdleCount;
  unsigned int threadSwitchCount;
  unsigned int reserved[8];
} iop_sys_status_t;


typedef struct {
  char name[56];
  u16 version;
  u16 flags;
  int id;
  u32 entry_addr;
  u32 gp_value;
  u32 text_addr;
  u32 text_size;
  u32 data_size;
  u32 bss_size;
  u32 lreserve[2];
} ModuleStatus;


typedef struct {
  int (*beforeOpen)(void *opt, const char *filename, int flag);
  int (*afterOpen)(void *opt, int fd);
  int (*close)(void *opt, int fd);
  int (*setBufSize)(void *opt, int fd, size_t nbyte);
  int (*beforeRead)(void *opt, int fd, size_t nbyte);
  int (*read)(void *opt, int fd, void *buf, size_t nbyte);
  int (*lseek)(void *opt, int fd, long offset, int whence);
  int (*getfsize)(void *opt, int fd);
} LDfilefunc;

typedef struct {
  char position;
  char access;
  char creserved[2];
  void *distaddr;
  int distoffset;
  LDfilefunc *functable;
  void *funcopt;
  int ireserved[3];
} LMWOoption;

typedef struct _iop_message {
  struct iop_message *next;
  unsigned char priority;
  unsigned char unused[3];
} iop_message_t;

typedef struct _iop_mbx_status {
  unsigned int attr;
  unsigned int option;
  int numWaitThreads;
  int numMessage;
  iop_message_t *topPacket;
  int reserved[2];
} iop_mbx_status_t;

typedef struct _exception_handler_struct_t
{
  void* next;
  int info;
  u32 funccode[];
} exception_handler_struct_t;

typedef exception_handler_struct_t* exception_handler_t;

typedef struct SecrBitBlockData{
  
  u32 size;
  
  u32 flags;
  u8 checksum[8];
} SecrBitBlockData_t;

typedef struct SecrBitTableHeader{
  
  u32 headersize;
  
  u8 block_count;
  u8 pad1;
  u8 pad2;
  u8 pad3;
} SecrBitTableHeader_t;


typedef struct SecrBitTable {
  SecrBitTableHeader_t header;
  
  SecrBitBlockData_t blocks[63];
} SecrBitTable_t;


typedef struct KELF_Header{
  u8 UserHeader[16];
  
  u32 ELF_size;
  
  u16 KELF_header_size; 
  u16 unknown5;
  
  u16 flags;
  
  u16 BIT_count;
  u32 mg_zones;
} SecrKELFHeader_t;


typedef void (*print_callback_t)(void *context, int c);


typedef struct {
  u8 stat;
  u8 second;
  u8 minute;
  u8 hour;
  u8 pad;
  u8 day;
  u8 month;
  u8 year;
} sceCdCLOCK;

typedef struct {
  u32 lsn;
  u32 size;
  char name[16];
  u8 date[8];
} sceCdlFILE;


typedef struct {
  
  u8 minute;
  
  u8 second;
  
  u8 sector;
  
  u8 track;
} sceCdlLOCCD;

typedef struct {
  u8 trycount;
  u8 spindlctrl;
  u8 datapattern;
  u8 pad;
} sceCdRMode;

typedef struct {
  
  u32 lbn;
  
  u32 sectors;
  
  u32 buffer;
} sceCdRChain;


typedef struct t_SifDmaTransfer
{
  void  *src;
  void  *dest;
  int size;
  int attr;
} SifDmaTransfer_t;


struct _sio2_dma_arg { 
  void  *addr;
  int size;
  int count;
};

typedef struct {
  u32 stat6c;

  u32 port_ctrl1[4];
  u32 port_ctrl2[4];

  u32 stat70;

  u32 regdata[16];

  u32 stat74;

  u32 in_size;
  u32 out_size;
  u8  *in;
  u8  *out;

  struct _sio2_dma_arg in_dma;
  struct _sio2_dma_arg out_dma;
} sio2_transfer_data_t;

typedef int (KprintfHandler_t)(void *context, const char *format, void * ap);

typedef void (*sceCdCBFunc)(int reason);

struct irx_export_table {
  u32 magic;
  struct irx_export_table *next;
  u16 version;
  u16 mode;
  u8  name[8];
  void  *fptrs[0];
};



typedef struct _IopModuleID {
    const char *name;
    unsigned short int version;
} IopModuleID_t;

typedef struct _FileInfo {
  u32 ModuleType;
  void *EntryPoint;
  void *gp;
  void *text_start;
  u32 text_size;
  u32 data_size;
  u32 bss_size;
  u32 MemSize;
  IopModuleID_t *mod_id;
} FileInfo_t;

typedef struct _ModuleInfo {
  struct _ModuleInfo *next;
  char  *name;
  u16 version;
  
  u16 newflags;
  u16 id;
  
  u16 flags;
  
  u32 entry;
  u32 gp;
  u32 text_start;
  u32 text_size;
  u32 data_size;
  u32 bss_size;
  u32 unused1;
  u32 unused2;
} ModuleInfo_t;

typedef struct _iop_library {
  struct  _iop_library *prev;
  struct  irx_import_table *caller;
  u16 version;
  u16 flags;
  char  name[8];
  void  *exports[0];
} iop_library_t;


typedef struct tag_LC_internals {
  iop_library_t* let_next, *let_prev; 
  iop_library_t* mda_next, *mda_prev;
  
  ModuleInfo_t *image_info;
  int module_count;
  int module_index;
} lc_internals_t;

typedef struct {
  u16 value;
  u8  id;
  u8  len;
  u32 data[0];
} iop_bootmode_t;


typedef struct{ 
  void *callback;
}iop_init_entry_t;

typedef int (*BootupCallback_t)(iop_init_entry_t* next, int delayed);


typedef int (*McCommandHandler_t)(int port, int slot, sio2_transfer_data_t *sio2_trans_data);
typedef int (*McDevIDHandler_t)(int port, int slot);

typedef struct t_SifCmdHeader {
  
  u32 psize:8;
  
  u32 dsize:24;
  
  void  *dest;
  
  int cid;
  
  u32 opt;
} SifCmdHeader_t;

typedef struct t_SifCmdSRegData {
  SifCmdHeader_t  header;
  int   index;
  unsigned int  value;
} SifCmdSRegData_t;

typedef void (*SifCmdHandler_t)(void *data, void *harg);

typedef struct t_SifCmdHandlerData
{
  SifCmdHandler_t handler;
  void    *harg;
} SifCmdHandlerData_t;

typedef struct _iop_reset_pkt {
  struct t_SifCmdHeader header;
  int arglen;
  int mode;
  char  arg[80];
} SifCmdResetData_t;


typedef int (*sio2_mtap_change_slot_cb_t)(s32 *status);
typedef int (*sio2_mtap_get_slot_max_cb_t)(int port);
typedef int (*sio2_mtap_get_slot_max2_cb_t)(int port);
typedef void (*sio2_mtap_update_slots_t)(void);

typedef int (*dev9_intr_cb_t)(int flag);
typedef void (*dev9_shutdown_cb_t)(void);
typedef void (*dev9_dma_cb_t)(int bcr, int dir);

typedef struct _ata_devinfo {
  /** Was successfully probed.  */
  s32 exists;
  /** Supports the PACKET command set.  */
  s32 has_packet;
  /** Total number of user sectors.  */
  u32 total_sectors;
  /** Word 0x100 of the identify info.  */
  u32 security_status;
  /** Supports the 48-bit LBA command set (unofficial).  */
  u32 lba48;
} ata_devinfo_t;

typedef struct __attribute__((aligned(4))) drvdrv_exec_cmd_ack_
{
  u16 command;
  u16 input_word[64];
  u32 input_word_count;
  u16 status_4220_ack;
  u16 ack_status_ack;
  u16 output_word[64];
  u32 status_4228_ack;
  u16 status_4220_comp;
  u16 comp_status;
  u16 return_result_word[64];
  u32 status_4228_comp;
  u32 timeout;
  void *input_buffer;
  u32 input_buffer_length;
  void *output_buffer;
  int ack_status_ack2;
  int phase;
} drvdrv_exec_cmd_ack;

typedef struct
{
  u16 func;
  u16 entry;
  u32 value;
} sceSdBatch;

typedef struct
{
  int     core;
  int     mode;
  short   depth_L;
  short   depth_R;
  int     delay;
  int     feedback;
} sceSdEffectAttr;

typedef int (*sceSdSpu2IntrHandler)(int, void *);
typedef int (*sceSdTransIntrHandler)(int, void *);
typedef int (*SdIntrCallback)(void *data);

typedef struct {
  u32 id;
  u32 mbits;
  u32 page_bytes; /* bytes/page */
  u32 block_pages;  /* pages/block */
  u32 blocks;
} flash_info_t;

typedef struct _sceMcStDateTime {
  u8  Resv2;
  u8  Sec;
  u8  Min;
  u8  Hour;
  u8  Day;
  u8  Month;
  u16 Year;
} sceMcStDateTime;

/* MCMAN public structures */
typedef struct {      // size = 128
  int mode;     // 0
  int length;     // 4
  s16 linked_block;   // 8
  char  name[20];     // 10
  u8  field_1e;     // 30
  u8  field_1f;     // 31
  sceMcStDateTime created;  // 32
  int field_28;     // 40
  u16 field_2c;     // 44
  u16 field_2e;     // 46
  sceMcStDateTime modified; // 48
  int field_38;     // 56
  u8  unused2[65];    // 60
  u8  field_7d;     // 125
  u8  field_7e;     // 126
  u8  edc;      // 127
} McFsEntryPS1;

typedef struct {      // size = 512
  u16 mode;     // 0
  u16 unused;     // 2
  u32 length;     // 4
  sceMcStDateTime created;  // 8
  u32 cluster;      // 16
  u32 dir_entry;      // 20
  sceMcStDateTime modified; // 24
  u32 attr;     // 32
  u32 unused2[7];     // 36
  char  name[32];     // 64
  u8  unused3[416];   // 96
} McFsEntry;

typedef struct _MCCacheEntry {
  int  cluster;   // 0
  u8  *cl_data;   // 4
  u16  mc_slot;   // 8
  u8   wr_flag;   // 10
  u8   mc_port;   // 11
  u8   rd_flag;   // 12
  u8   unused[3]; // 13
} McCacheEntry;

/** file descriptor related mc command
 * used by: McInit, McClose, McSeek, McRead, McWrite, McGetinfo, McFormat, McFlush, McUnformat
 */
typedef struct {  // size = 48
  int fd;   // 0
  int port; // 4
  int slot; // 8
  int size; // 12
  int offset; // 16
  int origin; // 20
  void *buffer; // 24
  void *param;  // 28
  u8 data[16];  // 32
} mcDescParam_t;

/** endParamenter struct
 * used by: McRead, McGetInfo, McReadPage
 */
typedef struct {    // size = 64
  union {
    s32 size1;  // 0
    s32 type;
  };
  union {
    s32 size2;  // 4
    s32 free;
  };
  void  *dest1;   // 8
  void  *dest2;   // 12
  u8  src1[16]; // 16
  u8  src2[16]; // 32
  u8  unused[16]; // 48
} mcEndParam_t;

/** endParamenter2 struct
 * used by: McRead2, McGetInfo2
 */
typedef struct {      // size = 192
  union {
    s32 size1;    // 0
    s32 type;
  };
  union {
    s32 size2;    // 4
    s32 free;
  };
  void  *dest1;     // 8
  void  *dest2;     // 12
  u8  src1[64];   // 16
  u8  src2[64];   // 80
  union {
    s32 formatted;  // 144
    u8  unused[48];
  };
} mcEndParam2_t;

typedef struct {
  s32 result;
  u32 mcserv_version;
  u32 mcman_version;
} mcRpcStat_t;

typedef struct _sceMcTblGetDir {  // size = 64
  sceMcStDateTime _Create;  // 0
  sceMcStDateTime _Modify;  // 8
  u32 FileSizeByte;   // 16
  u16 AttrFile;     // 20
  u16 Reserve1;     // 22
  u32 Reserve2;     // 24
  u32 PdaAplNo;     // 28
  unsigned char EntryName[32];  // 32
} sceMcTblGetDir;

// Audio related definitions start here

typedef struct {
  int   sema;
  void  *buff;
} sceCslBuffCtx;

typedef struct {
  int    system[48];
} sceCslIdMonitor;


typedef struct {
  int       buffNum;
  sceCslBuffCtx *buffCtx;
} sceCslBuffGrp;

typedef struct {
  int     buffGrpNum;
  sceCslBuffGrp*    buffGrp;
  void*     conf;
  void*     callBack;
  char**      extmod;
} sceCslCtx;

typedef struct {
  int   core;
#define SCEHS_REV_MODE_OFF    0
#define SCEHS_REV_MODE_ROOM   1
#define SCEHS_REV_MODE_STUDIO_A 2
#define SCEHS_REV_MODE_STUDIO_B 3
#define SCEHS_REV_MODE_STUDIO_C 4
#define SCEHS_REV_MODE_HALL   5
#define SCEHS_REV_MODE_SPACE  6
#define SCEHS_REV_MODE_ECHO   7
#define SCEHS_REV_MODE_DELAY  8
#define SCEHS_REV_MODE_PIPE   9
#define SCEHS_REV_MODE_MAX    10
#define SCEHS_REV_MODE_CLEAR_WA (1<<8)
  int   mode;
  short depth_L, depth_R;
  int   delay;
  int   feedback;
  short vol_l, vol_r;
} sceHSyn_EffectAttr;

#define sceHSyn_NumCore 2
#define sceHSyn_NumVoice 24

typedef struct {
  int pendingVoiceCount;
  int workVoiceCount;
  unsigned char voice_state[sceHSyn_NumCore][sceHSyn_NumVoice];
  unsigned short  voice_env[sceHSyn_NumCore][sceHSyn_NumVoice];
} sceHSyn_VoiceStat;

typedef struct {
  unsigned int  func;
  unsigned int  retVal;
  unsigned int  arg[5];
} sceHSyn_SdCall;
typedef struct {
  unsigned int  infoBlkNum;
  unsigned int  readIndex;
  unsigned int  writeIndex;
  sceHSyn_SdCall  sdCall[0];
} sceHSyn_DebugInfo;

typedef struct {
#define sceHSynChStat_KeyOn   (1<<0)
#define sceHSynChStat_Hold    (1<<1)
#define sceHSynChStat_KeyOff  (1<<2)
  unsigned char ch[16];
} sceHSynChStat;

typedef struct {
  unsigned char d[7];
} sceMSInHsMsg;

typedef struct {
  unsigned short sampleSetIndex;

  unsigned char  splitRangeLow;
  unsigned char  splitCrossFade;
  unsigned char  splitRangeHigh;
  unsigned char  splitNumber;

  unsigned short splitBendRangeLow;
  unsigned short splitBendRangeHigh;

  char     keyFollowPitch;
  unsigned char  keyFollowPitchCenter;
  char     keyFollowAmp;
  unsigned char  keyFollowAmpCenter;
  char     keyFollowPan;
  unsigned char  keyFollowPanCenter;

  unsigned char  splitVolume;
  char     splitPanpot;
  char     splitTranspose;
  char     splitDetune;
} sceHardSynthSplitBlock;


typedef struct {
  unsigned int   splitBlockAddr;

  unsigned char  nSplit;
  unsigned char  sizeSplitBlock;

  unsigned char  progVolume;
  char     progPanpot;
  char     progTranspose;
  char     progDetune;
  char     keyFollowPan;
  unsigned char  keyFollowPanCenter;
  unsigned char  progAttr;
  unsigned char  dmy;

  unsigned char  progLfoWave;
  unsigned char  progLfoWave2;
  unsigned char  progLfoStartPhase;
  unsigned char  progLfoStartPhase2;
  unsigned char  progLfoPhaseRandom;
  unsigned char  progLfoPhaseRandom2;
  unsigned short progLfoFreq;
  unsigned short progLfoFreq2;
  short    progLfoPitchDepth;
  short    progLfoPitchDepth2;
  short    progLfoMidiPitchDepth;
  short    progLfoMidiPitchDepth2;
  char     progLfoAmpDepth;
  char     progLfoAmpDepth2;
  char     progLfoMidiAmpDepth;
  char     progLfoMidiAmpDepth2;

  sceHardSynthSplitBlock splitBlock[0];
} sceHardSynthProgramParam;


typedef struct{
  unsigned int   volume;
  int            panpot;
  int            transpose;
  int            detune;
} SceSdHdProgramCommon;

typedef struct{
  int            pan;
  unsigned int   panCenter;
} SceSdHdProgramKeyFollow;


typedef struct{
  unsigned int   wavePitch;
  unsigned int   waveAmp;
  unsigned int   startPhasePitch;
  unsigned int   startPhaseAmp;
  unsigned int   phaseRandomPitch;
  unsigned int   phaseRandomAmp;
  unsigned int   cyclePitch;
  unsigned int   cycleAmp;
  int            pitchDepthUp;
  int            pitchDepthDown;
  int            midiPitchDepthUp;
  int            midiPitchDepthDown;
  int            ampDepthUp;
  int            ampDepthDown;
  int            midiAmpDepthUp;
  int            midiAmpDepthDown;
} SceSdHdProgramLFO;

typedef struct{
  unsigned int              nSplit;
  unsigned int              progAttr;
  SceSdHdProgramCommon      common;
  SceSdHdProgramKeyFollow   keyFollow;
  SceSdHdProgramLFO         LFO;
} SceSdHdProgramParam;

typedef struct {
  unsigned char  velCurve;
  unsigned char  velLimitLow;
  unsigned char  velLimitHigh;
  unsigned char  nSample;

  unsigned short sampleIndex[0];
} sceHardSynthSampleSetParam;

typedef struct{
  unsigned int   velCurve;
  unsigned int   velLimitLow;
  unsigned int   velLimitHigh;
  unsigned int   nSample;
} SceSdHdSampleSetParam;

typedef struct {
  unsigned short VagIndex;

  unsigned char  velRangeLow;
  unsigned char  velCrossFade;
  unsigned char  velRangeHigh;

  char     velFollowPitch;
  unsigned char  velFollowPitchCenter;
  unsigned char  velFollowPitchVelCurve;

  char     velFollowAmp;
  unsigned char  velFollowAmpCenter;
  unsigned char  velFollowAmpVelCurve;

  unsigned char  sampleBaseNote;
  char     sampleDetune;
  char     samplePanpot;
  unsigned char  sampleGroup;
  unsigned char  samplePriority;
  unsigned char  sampleVolume;
  unsigned char  dmy;

  unsigned short sampleAdsr1;
  unsigned short sampleAdsr2;

  char     keyFollowAr;
  unsigned char  keyFollowArCenter;
  char     keyFollowDr;
  unsigned char  keyFollowDrCenter;
  char     keyFollowSr;
  unsigned char  keyFollowSrCenter;
  char     keyFollowRr;
  unsigned char  keyFollowRrCenter;
  char     keyFollowSl;
  unsigned char  keyFollowSlCenter;

  unsigned short samplePitchLfoDelay;
  unsigned short samplePitchLfoFade;
  unsigned short sampleAmpLfoDelay;
  unsigned short sampleAmpLfoFade;

  unsigned char  sampleLfoAttr;
  unsigned char  sampleSpuAttr;
} sceHardSynthSampleParam;

typedef struct{
  unsigned int    low;
  unsigned int    crossFade;
  unsigned int    high;
} SceSdHdSampleVelRange;

typedef struct{
  int             pitch;
  unsigned int    pitchCenter;
  unsigned int    pitchVelCurve;
  int             amp;
  unsigned int    ampCenter;
  unsigned int    ampVelCurve;
} SceSdHdSampleVelFollow;

typedef struct{
  unsigned int    baseNote;
  int             detune;
  int             panpot;
  unsigned int    group;
  unsigned int    priority;
  unsigned int    volume;
} SceSdHdSampleCommon;

typedef struct{
  unsigned int   ADSR1;
  unsigned int   ADSR2;
} SceSdHdSampleADSR;

typedef struct{
  int             ar;
  unsigned int    arCenter;
  int             dr;
  unsigned int    drCenter;
  int             sr;
  unsigned int    srCenter;
  int             rr;
  unsigned int    rrCenter;
  int             sl;
  unsigned int    slCenter;
} SceSdHdSampleKeyFollow;

typedef struct{
  unsigned int   pitchLFODelay;
  unsigned int   pitchLFOFade;
  unsigned int   ampLFODelay;
  unsigned int   ampLFOFade;
} SceSdHdSampleLFO;

typedef struct{
  int                      vagIndex;
  unsigned int             spuAttr;
  unsigned int             lfoAttr;
  SceSdHdSampleVelRange    velRange;
  SceSdHdSampleVelFollow   velFollow;
  SceSdHdSampleCommon      common;
  SceSdHdSampleADSR        ADSR;
  SceSdHdSampleKeyFollow   keyFollow;
  SceSdHdSampleLFO         LFO;
} SceSdHdSampleParam;

typedef struct {
  unsigned int   vagOffsetAddr;
  unsigned short vagSampleRate;
  unsigned char  vagAttribute;
  unsigned char  dmy;
} sceHardSynthVagParam;

typedef struct{
  unsigned int   vagOffsetAddr;
  unsigned int   vagSize;
  unsigned int   vagSampleRate;
  unsigned int   vagAttribute;
} SceSdHdVAGInfoParam;

typedef struct{
  unsigned int    low;
  unsigned int    crossFade;
  unsigned int    high;
} SceSdHdSplitRange;

typedef struct{
  unsigned int   low;
  unsigned int   high;
} SceSdHdSplitBendRange;

typedef struct{
  int             pitch;
  unsigned int    pitchCenter;
  int             amp;
  unsigned int    ampCenter;
  int             pan;
  unsigned int    panCenter;
} SceSdHdSplitKeyFollow;

typedef struct{
  unsigned int    volume;
  int             panpot;
  int             transpose;
  int             detune;
} SceSdHdSplitCommon;

typedef struct{
  unsigned int            sampleSetIndex;
  unsigned int            splitNumber;
  SceSdHdSplitRange       range;
  SceSdHdSplitBendRange   bendRange;
  SceSdHdSplitKeyFollow   keyFollow;
  SceSdHdSplitCommon      common;
} SceSdHdSplitBlock;

typedef struct  {
  unsigned short compOption;
  unsigned short compTableSize;
  unsigned char  compTable[0];
} sceSeqMidiCompBlock;

typedef struct  {
  unsigned int   sequenceDataOffset;
  unsigned short Division;
  sceSeqMidiCompBlock compBlock[0]; /* compression data block:
             [NOTICE: sceSeqMidiDataBlock may have
            no compression data block] */
} sceSeqMidiDataBlock;

#define SCESDSQ_MAXMIDIMESSAGELENGTH       8
#define SCESDSQ_MAXORIGINALMESSAGELENGTH   12
#define SCESDSQ_MAXSONGMESSAGELENGTH       3

typedef struct{
  unsigned int                 readStatus;
  unsigned int                 midiNumber;
  sceSeqMidiDataBlock   *midiData;
  unsigned int                 offset;
  unsigned int                 nextOffset;
  unsigned int                 division;
  unsigned int                 compMode;
  unsigned int                 compTableSize;
  unsigned int                 deltaTime;
  unsigned char                lastStatus;
  unsigned char                reserve[3];
  unsigned int                 messageLength;
  unsigned char                message[SCESDSQ_MAXMIDIMESSAGELENGTH];
  unsigned int                 originalMessageLength;
  unsigned char                originalMessage[SCESDSQ_MAXORIGINALMESSAGELENGTH];
} SceSdSqMidiData;

typedef struct{
  unsigned int    readStatus;
  unsigned int    songNumber;
  void     *topAddr;
  unsigned int    offset;
  unsigned int    nextOffset;
  unsigned char   message[SCESDSQ_MAXSONGMESSAGELENGTH];
  unsigned char   reserve;
} SceSdSqSongData;

typedef struct{
  unsigned char   status;
  unsigned char   data;
} SceSdSqCompTableData, SceSdSqPolyKeyData;

typedef struct{
  unsigned char   status;
  unsigned char   note;
  unsigned char   velocity;
  unsigned char   reserve;
} SceSdSqCompTableNoteOnEvent;


typedef struct {
  short *src;
  short *dest;
  short *work;
  int    size;
  int    loop_start;
  int    loop;
  int    byte_swap;
  int    proceed;
  int    quality;
} sceSpuEncodeEnv;



















































