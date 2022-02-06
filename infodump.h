
// acata
/* 04 */ extern int acAtaModuleRestart (int argc, char **argv);
/* 05 */ extern int acAtaModuleStart (int argc, char **argv);
/* 06 */ extern int acAtaModuleStatus (void);
/* 07 */ extern int acAtaModuleStop (void);
/* 08 */ extern acAtaT acAtaSetup (acAtaData *ata, acAtaDone done, void *arg, u_int tmout);
/* 09 */ extern int acAtaRequest (acAtaT ata, int flag, acAtaCommandData *cmd, int item, void *buf, int size);
/* 10 */ extern int acAtaRequestI (acAtaT ata, int flag, acAtaCommandData *cmd, int item, void *buf, int size);
/* 11 */ extern acAtaCommandData *acAtaReply (acAtaT ata);
/* 12 */ extern int acAtaStatus (acAtaT ata);
/* 13 */ extern acAtapiT acAtapiSetup (acAtapiData *atapi, acAtapiDone done, void *arg, u_int tmout);
/* 14 */ extern int acAtapiRequest (acAtapiT atapi, int flag, acAtapiPacketData *pkt, void *buf, int size);
/* 15 */ extern int acAtapiRequestI (acAtapiT atapi, int flag, acAtapiPacketData *pkt, void *buf, int size);
/* 16 */ extern int acAtapiStatus (acAtapiT atapi);
/* 17 */ extern int ata_probe (acAtaReg atareg);

/* accdvd */
/* 04 */ extern int acCdvdModuleRestart (int argc, char **argv);
/* 05 */ extern int acCdvdModuleStart (int argc, char **argv);
/* 06 */ extern int acCdvdModuleStatus (void);
/* 07 */ extern int acCdvdModuleStop (void);


/* 10 */ extern int sceCdSearchFile (sceCdlFILE *fp, char *name);
/* 11 */ extern int sceCdRead (u_int lsn, u_int sectors, void *buf, sceCdRMode *mode);

/* 13 */ extern int *sceCdCallback (void (*func) (/* unknown */));
/* 14 */ extern int sceCdTrayReq (int mode, u_int *traycnt);
/* 15 */ extern u_int sceCdGetReadPos (void);
/* 16 */ extern int sceCdSync (int mode);
/* 17 */ extern int sceCdInit (int init_mode);

/* 19 */ extern int sceCdDiskReady (int mode);
/* 20 */ extern int sceCdGetError (void);
/* 21 */ extern int sceCdGetDiskType (void);
/* 22 */ extern int sceCdStatus (void);

/* 24 */ extern int sceCdGetToc (u_char *toc);
/* 25 */ extern int sceCdSeek (u_int lsn);
/* 26 */ extern int sceCdStandby (void);
/* 27 */ extern int sceCdStop (void);
/* 28 */ extern int sceCdPause (void);
/* 29 */ extern int sceCdStInit (u_int bufmax, u_int bankmax, u_int iop_bufaddr);
/* 30 */ extern int sceCdStStart (u_int lsn, sceCdRMode *mode);
/* 31 */ extern int sceCdStSeek (u_int lsn);
/* 32 */ extern int sceCdStStop (void);
/* 33 */ extern int sceCdStRead (u_int sectors, u_int *buf, u_int mode, u_int *err);
/* 34 */ extern int sceCdStStat (void);
/* 35 */ extern int sceCdStPause (void);
/* 36 */ extern int sceCdStResume (void);
/* 37 */ extern int sceCdMmode (int media);



/* 41 */ extern int cdc_module_restart (int argc, char **argv);
/* 42 */ extern int cdc_module_start (int argc, char **argv);
/* 43 */ extern int cdc_module_status (void);
/* 44 */ extern int cdc_module_stop (void);
/* 45 */ extern int cdc_geterrno (void);
/* 46 */ extern int cdc_getfno (void);
/* 47 */ extern int cdc_seterrno (int ret);
/* 48 */ extern int cdc_xfer (void *dst, void *src, int len, enum cdc_xfer_dir dir);
/* 49 */ extern int cdc_error (void);
/* 50 */ extern int cdc_lookup (sceCdlFILE *fp, char *name, int namlen, cdc_xfer_t xfer);
/* 51 */ extern int cdc_medium (void);
/* 52 */ extern int cdc_readtoc (u_char *toc, cdc_xfer_t xfer);
/* 53 */ extern int cdc_ready (int nonblocking);
/* 54 */ extern int cdc_sync (int nonblocking);
/* 55 */ extern int cdc_pause (cdc_done_t done);
/* 56 */ extern int cdc_standby (cdc_done_t done);
/* 57 */ extern int cdc_stat (void);
/* 58 */ extern int cdc_stop (cdc_done_t done);
/* 59 */ extern int cdc_tray (int mode, u_int *traycnt);
/* 60 */ extern int cdc_seek (u_int lsn, cdc_done_t done);
/* 61 */ extern int cdc_read (u_int lsn, void *buf, int sectors, sceCdRMode *mode, cdc_xfer_t xfer, cdc_done_t done);
/* 62 */ extern int cdc_getpos (void);
/* 63 */ extern int cdc_inits (void *buf, u_int size, u_int bsize);
/* 64 */ extern int cdc_seeks (u_int lsn);
/* 65 */ extern int cdc_reads (void *buf, int sectors, int mode, int *errp, cdc_xfer_t xfer);
/* 66 */ extern int cdc_starts (u_int lsn, sceCdRMode *mode);
/* 67 */ extern int cdc_stats (void);
/* 68 */ extern int cdc_stops (void);
/* 69 */ extern int cdc_pauses (void);
/* 70 */ extern int cdc_resumes (void);

// accore X
/* 04 */ extern int acDmaModuleRestart (int argc, char **argv);
/* 05 */ extern int acDmaModuleStart (int argc, char **argv);
/* 06 */ extern int acDmaModuleStatus (void);
/* 07 */ extern int acDmaModuleStop (void);
/* 08 */ extern acDmaT acDmaSetup (acDmaData *dma, acDmaOpsData *ops, int priority, int slice, int output);
/* 09 */ extern int acDmaRequest (acDmaT dma);
/* 10 */ extern int acDmaRequestI (acDmaT dma);
/* 11 */ extern int acDmaCancel (acDmaT dma, int result);
/* 12 */ extern int acDmaCancelI (acDmaT dma, int result);
/* 13 */ extern int acIntrModuleRestart (int argc, char **argv);
/* 14 */ extern int acIntrModuleStart (int argc, char **argv);
/* 15 */ extern int acIntrModuleStatus (void);
/* 16 */ extern int acIntrModuleStop (void);
/* 17 */ extern int acIntrRegister (acIntrNum inum, int (*func) (/* unknown */), void *arg);
/* 18 */ extern int acIntrRelease (acIntrNum inum);
/* 19 */ extern int acIntrEnable (acIntrNum inum);
/* 20 */ extern int acIntrDisable (acIntrNum inum);
/* 21 */ extern int acIntrClear (acIntrNum inum);

// acflash X
/* 04 */ extern int acFlashModuleRestart (int argc, char **argv);
/* 05 */ extern int acFlashModuleStart (int argc, char **argv);
/* 06 */ extern int acFlashModuleStatus (void);
/* 07 */ extern int acFlashModuleStop (void);
/* 08 */ extern int acFlashStart (void);
/* 09 */ extern int acFlashStatus (acFlashAddr addr);
/* 10 */ extern int acFlashStop (void);
/* 11 */ extern int acFlashInfo (acFlashInfoData *info);
/* 12 */ extern int acFlashErase (acFlashAddr addr);
/* 13 */ extern int acFlashProgram (acFlashAddr addr, void *buf, int count);
/* 14 */ extern int acFlashRead (acFlashAddr addr, void *buf, int count);
/* 15 */ extern int acFlashVerify (acFlashAddr addr, void *buf, int count);

// acjv X
/* 04 */ extern int acJvModuleRestart (int argc, char **argv);
/* 05 */ extern int acJvModuleStart (int argc, char **argv);
/* 06 */ extern int acJvModuleStatus (void);
/* 07 */ extern int acJvModuleStop (void);
/* 08 */ extern int acJvRead (acJvAddr addr, void *buf, int size);
/* 09 */ extern int acJvWrite (acJvAddr addr, void *buf, int size);
/* 10 */ extern int acJvGet (acJvAddr addr);
/* 11 */ extern int acJvPut (acJvAddr addr, int value);

// acmem X
/* 04 */ extern int acMemModuleRestart (int argc, char **argv);
/* 05 */ extern int acMemModuleStart (int argc, char **argv);
/* 06 */ extern int acMemModuleStatus (void);
/* 07 */ extern int acMemModuleStop (void);
/* 08 */ extern acMemT acMemSetup (acMemData *mem, void *buf, int size);
/* 09 */ extern int acMemSend (acMemT mem, acMemEEaddr addr, int size, int retry);
/* 10 */ extern int acMemReceive (acMemT mem, acMemEEaddr addr, int size);
/* 11 */ extern int acMemWait (acMemT mem, int threshold, int retry);

// acmeme X
/* 04 */ extern int acMemeModuleRestart (int argc, char **argv);
/* 05 */ extern int acMemeModuleStart (int argc, char **argv);
/* 06 */ extern int acMemeModuleStatus (void);
/* 07 */ extern int acMemeModuleStop (void);

// acram X
/* 04 */ extern int acRamModuleRestart (int argc, char **argv);
/* 05 */ extern int acRamModuleStart (int argc, char **argv);
/* 06 */ extern int acRamModuleStatus (void);
/* 07 */ extern int acRamModuleStop (void);
/* 08 */ extern acRamT acRamSetup (acRamData *ram, acRamDone done, void *arg, int tmout);
/* 09 */ extern int acRamRead (acRamT ram, acRamAddr addr, void *buf, int count);
/* 10 */ extern int acRamReadI (acRamT ram, acRamAddr addr, void *buf, int count);
/* 11 */ extern int acRamWrite (acRamT ram, acRamAddr addr, void *buf, int count);
/* 12 */ extern int acRamWriteI (acRamT ram, acRamAddr addr, void *buf, int count);

// acsram X
/* 04 */ extern int acSramModuleRestart (int argc, char **argv);
/* 05 */ extern int acSramModuleStart (int argc, char **argv);
/* 06 */ extern int acSramModuleStatus (void);
/* 07 */ extern int acSramModuleStop (void);
/* 08 */ extern int acSramRead (acSramAddr addr, void *buf, int size);
/* 09 */ extern int acSramWrite (acSramAddr addr, void *buf, int size);

// actimer X
// Yes, this is not a typo, start is 04
/* 04 */ extern int acTimerModuleStart (int argc, char **argv);
/* 05 */ extern int acTimerModuleRestart (int argc, char **argv);
/* 06 */ extern int acTimerModuleStop (void);
/* 07 */ extern int acTimerModuleStatus (void);
/* 08 */ extern int acTimerAdd (acTimerT timer, acTimerDone done, void *arg, u_int us);
/* 09 */ extern int acTimerRemove (acTimerT timer);

// acuart X
/* 04 */ extern int acUartModuleRestart (int argc, char **argv);
/* 05 */ extern int acUartModuleStart (int argc, char **argv);
/* 06 */ extern int acUartModuleStatus (void);
/* 07 */ extern int acUartModuleStop (void);
/* 08 */ extern int acUartRead (void *buf, int count);
/* 09 */ extern int acUartWrite (void *buf, int count);
/* 10 */ extern int acUartWait (acUartFlag rw, int usec);
/* 11 */ extern int acUartGetAttr (acUartAttrData *attr);
/* 12 */ extern int acUartSetAttr (acUartAttrData *attr);

// acdev R
/* 04 */ // SetAcMemDelayReg
/* 05 */ // GetAcMemDelayReg
/* 06 */ // SetAcIoDelayReg
/* 07 */ // GetAcIoDelayReg

// dmacman R
// dmac_request -> sceSetSliceDMA
// dmac_transfer -> sceStartDMA
// dmac_ch_set_dpcr -> sceSetDMAPriority
// dmac_enable -> sceEnableDMAChannel
// dmac_disable -> sceDisableDMAChannel

// mcman R
// McDetectCard2 -> mciConfInsert

// thbase R
/* 29 */ // SuspendThread
/* 30 */ // iSuspendThread
/* 31 */ // ResumeThread
/* 32 */ // iResumeThread


