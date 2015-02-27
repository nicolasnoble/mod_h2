/* Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __mod_h2__h2_task_output__
#define __mod_h2__h2_task_output__

/* h2_task_output reads a HTTP/1 response from the brigade and applies
 * them to a h2_output_converter. The brigade is setup as the output brigade
 * for our pseudo httpd conn_rec that is handling a specific h2_task.
 * 
 * The conversion is implemented in h2_response.
 */
struct h2_bucket;
struct h2_mplx;
struct h2_response;

typedef struct h2_task_output h2_task_output;

typedef apr_status_t (*h2_output_converter)(struct h2_bucket *bucket,
                                            void *conv_data,
                                            const char *data, apr_size_t len,
                                            apr_size_t *pconsumed);

h2_task_output *h2_task_output_create(apr_pool_t *pool,
                                      int session_id, int stream_id,
                                      struct h2_mplx *m);

void h2_task_output_destroy(h2_task_output *output);

apr_status_t h2_task_output_open(h2_task_output *output,
                                 struct h2_response *response);


apr_status_t h2_task_output_write(h2_task_output *output,
                                  ap_filter_t* filter,
                                  apr_bucket_brigade* brigade);

void h2_task_output_close(h2_task_output *output);

void h2_task_output_set_converter(h2_task_output *output,
                                  h2_output_converter conv,
                                  void *conv_ctx);

#endif /* defined(__mod_h2__h2_task_output__) */