#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/support/log.h>

#include "helloworld.grpc-c.h"

void handle_request(HelloRequest *request, HelloResponse *response) {
    // Process the request and fill in the response
    response->message = "Hello, world!";
}

int main(int argc, char **argv) {
    grpc_server *server;
    grpc_completion_queue *cq;
    grpc_credentials *creds;
    grpc_call *call;
    grpc_call_details call_details;
    grpc_metadata_array request_metadata_recv;
    grpc_metadata_array response_metadata_send;
    grpc_slice host, method;
    grpc_byte_buffer *request_payload = NULL;
    grpc_byte_buffer *response_payload = NULL;
    grpc_status_code status;
    grpc_slice status_details;
    grpc_call_error error;

    // Initialize gRPC and create a server
    grpc_init();
    server = grpc_server_create(NULL, NULL);
    creds = grpc_ssl_credentials_create(NULL, NULL, NULL, NULL, 0);
    grpc_server_credentials_set(server, creds, NULL, NULL, 0);
    grpc_server_register_completion_queue(server, cq, NULL);
    grpc_server_add_insecure_http2_port(server, "0.0.0.0:50051");
    grpc_server_start(server);

    // Wait for incoming requests
    while (1) {
        error = grpc_server_request_call(server, &call, &call_details,
                                         &request_metadata_recv, cq, cq, NULL);
        if (error != GRPC_CALL_OK) {
            break;
        }

        // Receive the request payload
        error = grpc_call_recv_message(call, &request_payload);
        if (error != GRPC_CALL_OK) {
            grpc_call_destroy(call);
            break;
        }

        // Deserialize the request message
        HelloRequest request;
        grpc_byte_buffer_reader bbr;
        grpc_byte_buffer_reader_init(&bbr, request_payload);
        grpc_c_deserialize(bbr, &request, HelloRequest_fields, 1);
        grpc_byte_buffer_reader_destroy(&bbr);

        // Process the request and fill in the response message
        HelloResponse response;
        handle_request

            // Serialize the response message
            grpc_byte_buffer *response_payload;
        grpc_c_serialize(&response, HelloResponse_fields, 1, &response_payload);

        // Send the response payload
        error = grpc_call_send_message(call, response_payload);
        if (error != GRPC_CALL_OK) {
            grpc_call_destroy(call);
            break;
        }

        // Send the status
        status = GRPC_STATUS_OK;
        status_details = grpc_empty_slice();
        error = grpc_call_send_status_from_server(call, status, &status_details,
                                                  &response_metadata_send, NULL);
        if (error != GRPC_CALL_OK) {
            grpc_call_destroy(call);
            break;
        }

        // Destroy the call
        grpc_call_destroy(call);
    }

    // Destroy the server
    grpc_server_destroy(server);
    grpc_shutdown();

    return 0;
}
