/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
#include "fcb_test.h"

TEST_CASE_SELF(fcb_test_init)
{
    int rc;
    struct fcb2 *fcb;

    fcb_tc_pretest(2);

    fcb = &test_fcb;
    memset(fcb, 0, sizeof(*fcb));

    rc = fcb2_init(fcb);
    TEST_ASSERT(rc == FCB2_ERR_ARGS);

    fcb->f_ranges = test_fcb_ranges;

    rc = fcb2_init(fcb);
    TEST_ASSERT(rc == FCB2_ERR_ARGS);

    fcb->f_sector_cnt = 2;
    fcb->f_magic = 0x12345678;
    fcb->f_range_cnt = 1;
    fcb->f_ranges[0].fsr_flash_area.fa_size =
              2 * fcb->f_ranges[0].fsr_sector_size;
    rc = fcb2_init(fcb);
    TEST_ASSERT(rc == FCB2_ERR_MAGIC);

    fcb->f_magic = 0;
    rc = fcb2_init(fcb);
    TEST_ASSERT(rc == 0);
}
