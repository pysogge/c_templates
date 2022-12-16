#include <aws/s3/s3.h>

int main(int argc, char **argv) {
    // Set up the S3 client
    struct aws_allocator *allocator = aws_default_allocator();
    struct aws_client_options options = {0};
    options.allocator = allocator;
    struct aws_client *client = aws_client_new(allocator, &options);

    // Set up the S3 put object request
    struct aws_byte_buf bucket = aws_byte_buf_from_c_str("my-bucket");
    struct aws_byte_buf key = aws_byte_buf_from_c_str("my-key");
    struct aws_input_stream *input_stream = NULL;  // Set this to the input stream for the file you want to upload
    struct aws_s3_put_object_request request = {
        .client = client,
        .bucket = bucket,
        .key = key,
        .content_length = 0,  // Set this to the size of the file in bytes
        .body = input_stream,
    };

    // Send the S3 put object request and handle the response
    struct aws_s3_put_object_response *response = NULL;
    aws_s3_put_object(&request, &response);
    if (response->error) {
        // Handle the error
    } else {
        // The file was successfully uploaded to S3
    }
}

// function to initialize a new S3 client

