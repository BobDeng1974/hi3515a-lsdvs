#if 0
// ��ȡ¼���ļs�������ļs¼�������G�
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define REC_FILENAME "./rec.h264"

typedef struct _PackHead_
{
	unsigned char 	packType;    // ����G�, 0:��Ƶ��; 1:��Ƶ��; 2:���ܰ�
	unsigned char	frameHeadLen;    // ֡ͷ����,�ó��ȸ��IpackType ��ֵ�仯��ȡ sizeof(��ͬ�Ľṹ��)    
	char	reserved[2];
} PACK_HEAD_T;

// ����Ƶ֡ͷ����
typedef struct _FrameHead_
{
    unsigned int  frameLen;            // ֡��������
    unsigned int  frameNo;            // ֡��,�����I��
    unsigned char videoStandard;    // ��Ƶ:��׼ 0,PAL; 1,NTSC. // ��Ƶ:ͨ��ģʽ, 0:��ͨ��, 1:������, Ĭ��ֵ 0
    unsigned char videoResolution;    // ��Ƶ:�ֱ��� 0,qcif; 1,cif; 2,hd1; 3,d1. // ��Ƶ:������, 0:8k, 1:16k, Ĭ��ֵ 0
    unsigned char frameRate;          // ��Ƶ:֡��. // ��Ƶ:λ��,0:8bits, 1:16bits, Ĭ��ֵ 1
    unsigned char frameType;         // ��Ƶ:֡��G� 5,I֡; 1,P֡ . // ��Ƶ::���뷽ʽ,0:adpcm, 1:g711, 2:g726, Ĭ��ֵ 0
    unsigned int  sec;                // �ӱ��ػ�ȡ��ʱ��,��
    unsigned int  usec;                // �ӱ��ػ�ȡ��ʱ��,΢��
    unsigned long long  pts;                // �Ӻ�˼�ײ��ȡ��ʱ���,(΢��)
} FRAME_HEAD_ST;

 
 typedef struct _StreamHead_
 {
 	PACK_HEAD_T 	packHead;
 	FRAME_HEAD_ST	frameHead;
 } STREAM_HEAD_T;

static void PrintFrameHead( STREAM_HEAD_T *streamHead )
{
	printf( "pt(%u), fhl(%u), fl(%u), fn(%u), vs(%u), vr(%u), fr(%u), ft(%u)!\r\n",
    	streamHead->packHead.packType,
    	streamHead->packHead.frameHeadLen,
    	streamHead->frameHead.frameLen,
    	streamHead->frameHead.frameNo,
    	streamHead->frameHead.videoStandard,
    	streamHead->frameHead.videoResolution,
    	streamHead->frameHead.frameRate,
    	streamHead->frameHead.frameType
        );
}
 
 int main()
 {
	int fd, ret;
	unsigned int lastFrameNo, totalReadSize = 0;
	static char buf[1024*1024];
	STREAM_HEAD_T streamHead;
	fd = open( REC_FILENAME, O_RDONLY );

	ret = read( fd, &streamHead, sizeof(streamHead) );
	if( ret <= 0 )
    {
    	return 0;
    }
	totalReadSize += ret;
    
	printf( "totalReadSize = %u\r\n", totalReadSize );
	ret = read( fd, buf, streamHead.frameHead.frameLen );
	if( ret <= 0 )
    {
    	return 0;
    }
	totalReadSize += ret;
    
	printf( "totalReadSize = %u\r\n", totalReadSize );
	lastFrameNo = streamHead.frameHead.frameNo;
	printf( "start test\r\n" );
	while( 1 )
    {        
    	ret = read( fd, &streamHead, sizeof(streamHead) );
    	if( ret <= 0 )
        {
        	printf( "ret(%d) = read(streamHead)\r\n", ret );
        	break;
        }
    	totalReadSize += ret;
        
    	printf( "totalReadSize = %u\r\n", totalReadSize );
    	PrintFrameHead( &streamHead );
    	ret = read( fd, buf, streamHead.frameHead.frameLen );
    	if( ret <= 0 )
        {            
        	printf( "ret(%d) = read(buf)\r\n", ret );
        	break;
        }
    	totalReadSize += ret;
        
    	printf( "totalReadSize = %u\r\n", totalReadSize );
        #if 0
    	if( 1 != (streamHead.frameHead.frameNo - lastFrameNo) )
        {
        	printf( "1 != (streamHead.frameHead.frameNo - lastFrameNo)\r\n" );
        	break;
        }
        #endif
    	lastFrameNo = streamHead.frameHead.frameNo;
    }
    
	printf( "stop test\r\n" );

	return 0;
}

#endif //

