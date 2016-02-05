

#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif   
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
//#include <libswscale/swscale.h>
#ifdef __cplusplus  
}
#endif

/*
Notes for building ffmpeg and linking to ffmpeg libraries.
1.  When you build ffmpeg, make sure and use the ./configure --enable-shared
2.  link against the avformat and avcodec libs in /usr/local/lib.
3.  Make sure that you extern "C" includes as above for C++ projects.
*/

int
main(int argc, char* argv[])
{
    
    av_register_all();

    AVFormatContext* p_format_ctx(NULL);

    // open the video file
    if (avformat_open_input(&p_format_ctx, argv[1], NULL, NULL) != 0)
	return -1; // could not find the file
    // retrieve the stream info
    if (avformat_find_stream_info(p_format_ctx, NULL) < 0)
	return -1;
    // dump
    av_dump_format(p_format_ctx, 0, argv[1], 0);

    //AVCodecContext* p_codec_ctx_orig(NULL);
    

    // Find the first video stream
    int video_stream(-1);
    for (unsigned int i = 0; i < p_format_ctx->nb_streams; i++)
	if (p_format_ctx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
	{
	    video_stream = static_cast<int>(i);
	    break;
	}
    if (video_stream == -1)
	return -1; // Didn't find a video stream

    // Get a pointer to the codec context for the video stream
    AVCodecContext* p_codec_ctx_orig = p_format_ctx->streams[video_stream]->codec;


    // Find the decoder for the video stream
    AVCodec* p_codec = avcodec_find_decoder(p_codec_ctx_orig->codec_id);
    if (p_codec == NULL)
    {
	std::cerr << "Unsupported codec!" << std::endl;
	return -1; // Codec not found
    }

    // Copy context
    AVCodecContext* p_codec_ctx = avcodec_alloc_context3(p_codec);
    
    if (avcodec_copy_context(p_codec_ctx, p_codec_ctx_orig) != 0)
    {
	std::cerr << "Couldn't copy codec context" << std::endl;
	return -1; // Error copying codec context
    }

    // Open codec
    if (avcodec_open2(p_codec_ctx, p_codec, NULL) < 0)
	return -1; // Could not open codec

    // Allocate video frame
    AVFrame* p_frame = av_frame_alloc();
    // allocate frame struct for RGB
    AVFrame* p_frame_RGB = av_frame_alloc();

    // Determine required buffer size and allocate buffer
    int num_bytes = avpicture_get_size(AV_PIX_FMT_RGB24, p_codec_ctx->width, p_codec_ctx->height);

    // buffer pointer
    uint8_t* buffer = reinterpret_cast<uint8_t*>(av_malloc(num_bytes * sizeof(uint8_t)));
    
    // free the RGB frame struct
    av_free(p_frame_RGB);
    // Free the YUV frame
    av_free(p_frame);
    
    // Close the codecs
    avcodec_close(p_codec_ctx);
    avcodec_close(p_codec_ctx_orig);

    // Close the video file
    avformat_close_input(&p_format_ctx);

    
    return 0;
}
