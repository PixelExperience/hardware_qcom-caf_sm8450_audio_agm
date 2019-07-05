/*
 * Copyright (c) 2019, The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of The Linux Foundation nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#define LOGTAG "AGM"
#include "agm_api.h"
#include "device.h"
#include "session_obj.h"
#include "utils.h"
#include <stdio.h>

int agm_init()
{
	session_obj_init();
	return 0;
}

int agm_deinit()
{
	//close all sessions first
	session_obj_deinit();

	return 0;
}

int agm_get_aif_info_list(struct aif_info *aif_list, size_t *num_aif_info)
{
	if (!num_aif_info || ((*num_aif_info != 0) && !aif_list)) {
		AGM_LOGE("%s: Error Invalid params\n", __func__);
		return -EINVAL;
	}

	return device_get_aif_info_list(aif_list, num_aif_info);
}

int agm_aif_set_metadata(uint32_t aif_id,
	struct agm_meta_data *metadata)
{
	struct device_obj *obj = NULL;
	int32_t ret = 0;

	ret = device_get_obj(aif_id, &obj);
	if (ret) {
		printf("%s: Error:%d retrieving device obj with audio_intf id=%d\n", __func__, ret, aif_id);
		goto done;
	}

	ret = device_set_metadata(obj, metadata);
	if (ret) {
		AGM_LOGE("%s: Error:%d setting metadata device obj with audio_intf id=%d\n", __func__, ret, aif_id);
		goto done;
	}

done:
	return ret;
}

int agm_aif_set_media_config(uint32_t aif_id,
	struct agm_media_config *media_config)
{
	struct device_obj *obj = NULL;
	int ret = 0;

	ret = device_get_obj(aif_id, &obj);
	if (ret) {
		AGM_LOGE("%s: Error:%d, retrieving device obj with audio_intf id=%d\n", __func__, ret, aif_id);
		goto done;
	}

	ret = device_set_media_config(obj, media_config);
	if (ret) {
		AGM_LOGE("%s: Error:%d setting mediaconfig device obj with audio_intf id=%d\n", __func__, ret, aif_id);
		goto done;
	}

done:
	return ret;
}

int agm_session_set_metadata(uint32_t session_id,
	struct agm_meta_data *metadata)
{

	struct session_obj *obj = NULL;
	int ret = 0;

	ret = session_obj_get(session_id, &obj);
	if (ret) {
		AGM_LOGE("%s: Error:%d retrieving session obj with session id=%d\n", __func__, ret, session_id);
		goto done;
	}

	ret = session_obj_set_sess_metadata(obj, metadata);
	if (ret) {
		AGM_LOGE("%s: Error:%d setting metadata for session obj with session id=%d\n", __func__, ret, session_id);
		goto done;
	}

done:
	return ret;
}

int agm_session_aif_set_metadata(uint32_t session_id,
	uint32_t aif_id,
	struct agm_meta_data *metadata)
{

	struct session_obj *obj = NULL;
	int ret = 0;

	ret = session_obj_get(session_id, &obj);
	if (ret) {
		AGM_LOGE("%s: Error:%d retrieving session obj with session id=%d\n", __func__, ret, session_id);
		goto done;
	}

	ret = session_obj_set_sess_aif_metadata(obj, aif_id, metadata);
	if (ret) {
		AGM_LOGE("%s: Error:%d setting metadata for session obj with session id=%d, aif_id=%d\n",
				__func__, ret, session_id, aif_id);
		goto done;
	}

done:
	return ret;
}

int agm_session_aif_get_tag_module_info(uint32_t session_id,
		uint32_t aif_id, void *payload, size_t *size)
{
	struct session_obj *obj = NULL;
	int ret = 0;

	ret = session_obj_get(session_id, &obj);
	if (ret) {
		AGM_LOGE("%s: Error:%d retrieving session obj with session id=%d\n", __func__, ret, session_id);
		goto done;
	}

	ret = session_obj_get_tag_with_module_info(obj, aif_id, payload, size);
	if (ret) {
		AGM_LOGE("%s: Error:%d setting parameters for session obj with session id=%d, aif_id=%d\n",
				__func__, ret, session_id, aif_id);
		goto done;
	}

done:
	return ret;
}

int agm_session_aif_set_cal(uint32_t session_id,
	uint32_t aif_id,
	struct agm_cal_config *cal_config)
{
	struct session_obj *obj = NULL;
	int ret = 0;

	ret = session_obj_get(session_id, &obj);
	if (ret) {
		AGM_LOGE("%s: Error:%d retrieving session obj with session id=%d\n", __func__, ret, session_id);
		goto done;
	}

	ret = session_obj_set_sess_aif_cal(obj, aif_id, cal_config);
	if (ret) {
		AGM_LOGE("%s: Error:%d setting calibration for session obj with session id=%d, aif_id=%d\n",
				__func__, ret, session_id, aif_id);
		goto done;
	}

done:
	return ret;
}

int agm_session_aif_set_params(uint32_t session_id,
	uint32_t aif_id,
	void* payload, size_t size)
{
	struct session_obj *obj = NULL;
	int ret = 0;

	ret = session_obj_get(session_id, &obj);
	if (ret) {
		AGM_LOGE("%s: Error:%d retrieving session obj with session id=%d\n", __func__, ret, session_id);
		goto done;
	}

	ret = session_obj_set_sess_aif_params(obj, aif_id, payload, size);
	if (ret) {
		AGM_LOGE("%s: Error:%d setting parameters for session obj with session id=%d, aif_id=%d\n",
				__func__, ret, session_id, aif_id);
		goto done;
	}

done:
	return ret;
}

int agm_session_set_params(uint32_t session_id,
	void* payload, size_t size)
{
	struct session_obj *obj = NULL;
	int ret = 0;

	ret = session_obj_get(session_id, &obj);
	if (ret) {
		AGM_LOGE("%s: Error:%d retrieving session obj with session id=%d\n", __func__, ret, session_id);
		goto done;
	}

	ret = session_obj_set_sess_params(obj, payload, size);
	if (ret) {
		AGM_LOGE("%s: Error:%d setting parameters for session obj with session id=%d\n",
				__func__, ret, session_id);
		goto done;
	}

done:
	return ret;
}

int agm_set_params_with_tag(uint32_t session_id, uint32_t aif_id, struct agm_tag_config *tag_config)
{
	struct session_obj *obj = NULL;
	int ret = 0;

	ret = session_obj_get(session_id, &obj);
	if (ret) {
		AGM_LOGE("%s: Error:%d retrieving session obj with session id=%d\n", __func__, ret, session_id);
		goto done;
	}

	ret = session_obj_set_sess_aif_params_with_tag(obj, aif_id, tag_config);
	if (ret) {
		AGM_LOGE("%s: Error:%d setting parameters for session obj with session id=%d\n",
				__func__, ret, session_id);
		goto done;
	}

done:
	return ret;
}

int agm_session_register_cb(uint32_t session_id, agm_event_cb cb, enum event_type evt_type, void *client_data)
{
	struct session_obj *obj = NULL;
	int ret = 0;

	ret = session_obj_get(session_id, &obj);
	if (ret) {
		AGM_LOGE("%s: Error:%d retrieving session obj with session id=%d\n", __func__, ret, session_id);
		goto done;
	}

	ret = session_obj_register_cb(obj, cb, evt_type, client_data);
	if (ret) {
		AGM_LOGE("%s: Error:%d registering callback for session obj with session id=%d\n", __func__, ret, session_id);
		goto done;
	}

done:
	return ret;
}

int agm_session_register_for_events(uint32_t session_id, struct agm_event_reg_cfg *evt_reg_cfg)
{
	struct session_obj *obj = NULL;
	int ret = 0;

	if (!evt_reg_cfg) {
		AGM_LOGE("%s: Invalid ev_reg_cfg for session id=%d\n", __func__, session_id);
		ret = -EINVAL;
		goto done;
	}

	ret = session_obj_get(session_id, &obj);
	if (ret) {
		AGM_LOGE("%s: Error:%d retrieving session obj with session id=%d\n", __func__, ret, session_id);
		goto done;
	}

	ret = session_obj_register_for_events(obj, evt_reg_cfg);
	if (ret) {
		AGM_LOGE("%s: Error:%d registering event for session obj with session id=%d\n", __func__, ret, session_id);
		goto done;
	}

done:
	return ret;
}

int agm_session_aif_connect(uint32_t session_id,
	uint32_t aif_id,
	bool state)
{

	struct session_obj *obj = NULL;
	int ret = 0;

	ret = session_obj_get(session_id, &obj);
	if (ret) {
		AGM_LOGE("%s: Error:%d retrieving session obj with session id=%d\n", __func__, ret, session_id);
		goto done;
	}

	ret = session_obj_sess_aif_connect(obj, aif_id, state);
	if (ret) {
		AGM_LOGE("%s: Error:%d Connecting aifid:%d with session id=%d\n", __func__, ret, aif_id, session_id);
		goto done;
	}

done:
	return ret;
}

int agm_session_open(uint32_t session_id, struct session_obj **handle)
{

	if (!handle) {
		AGM_LOGE("Invalid handle\n");
		return -1; //-EINVALID;
	}

	return session_obj_open(session_id, handle);
}

int agm_session_set_config(struct session_obj *handle,
	struct agm_session_config *stream_config,
	struct agm_media_config *media_config,
	struct agm_buffer_config *buffer_config) 
{
	if (!handle) {
		AGM_LOGE("Invalid handle\n");
		return -EINVAL;
	}

	return session_obj_set_config(handle, stream_config, media_config, buffer_config);
}

int agm_session_prepare(struct session_obj *handle)
{
	if (!handle) {
		AGM_LOGE("%s Invalid handle\n", __func__);
		return -1; //-EINVAL;
	}

	return session_obj_prepare(handle);
}

int agm_session_start(struct session_obj *handle)
{
	if (!handle) {
		AGM_LOGE("%s Invalid handle\n", __func__);
		return -EINVAL;
	}

	return session_obj_start(handle);
}

int agm_session_stop(struct session_obj *handle)
{
	if (!handle) {
		AGM_LOGE("%s Invalid handle\n", __func__);
		return -EINVAL;
	}

	return session_obj_stop(handle);
}

int agm_session_close(struct session_obj *handle)
{
	if (!handle) {
		AGM_LOGE("%s Invalid handle\n", __func__);
		return -EINVAL;
	}

	return session_obj_close(handle);
}

int agm_session_pause(struct session_obj *handle)
{
	if (!handle) {
		AGM_LOGE("%s Invalid handle\n", __func__);
		return -EINVAL;
	}

	return session_obj_pause(handle);
}

int agm_session_resume(struct session_obj *handle)
{
	if (!handle) {
		AGM_LOGE("%s Invalid handle\n", __func__);
		return -EINVAL;
	}

	return session_obj_resume(handle);
}

int agm_session_write(struct session_obj *handle, void *buff, size_t *count)
{
	if (!handle) {
		AGM_LOGE("%s Invalid handle\n", __func__);
		return -EINVAL;
	}

	return session_obj_write(handle, buff, count);
}

int agm_session_read(struct session_obj *handle, void *buff, size_t *count)
{
	if (!handle) {
		AGM_LOGE("%s Invalid handle\n", __func__);
		return -EINVAL;
	}

	return session_obj_read(handle, buff, count);
}

size_t agm_get_hw_processed_buff_cnt(struct session_obj *handle, enum direction dir)
{
	if (!handle) {
		AGM_LOGE("%s Invalid handle\n", __func__);
		return -EINVAL;
	}

	return session_obj_hw_processed_buff_cnt(handle, dir);
}

int agm_session_set_loopback(uint32_t capture_session_id, uint32_t playback_session_id, bool state)
{
	struct session_obj *obj = NULL;
	int ret = 0;

	ret = session_obj_get(capture_session_id, &obj);
	if (ret) {
		AGM_LOGE("%s: Error:%d retrieving session obj with session id=%d\n", __func__, ret, capture_session_id);
		goto done;
	}

	ret = session_obj_set_loopback(obj, playback_session_id, state);
	if (ret) {
		AGM_LOGE("%s: Error:%d setting loopback for session obj with session id=%d\n", __func__, ret, capture_session_id);
		goto done;
	}

done:
	return ret;
}


int agm_session_set_ec_ref(uint32_t capture_session_id, uint32_t aif_id, bool state)
{
	struct session_obj *obj = NULL;
	int ret = 0;

	ret = session_obj_get(capture_session_id, &obj);
	if (ret) {
		AGM_LOGE("%s: Error:%d retrieving session obj with session id=%d\n", __func__, ret, capture_session_id);
		goto done;
	}

	ret = session_obj_set_ec_ref(obj, aif_id, state);
	if (ret) {
		AGM_LOGE("%s: Error:%d setting ec_ref for session obj with session id=%d\n", __func__, ret, capture_session_id);
		goto done;
	}

done:
	return ret;
}

int agm_session_eos(struct session_obj *handle)
{
	if (!handle) {
		AGM_LOGE("%s Invalid handle\n", __func__);
		return -EINVAL;
	}

	return session_obj_eos(handle);
}

int agm_get_session_time(struct session_obj *handle, uint64_t *timestamp)
{
	if (!handle || !timestamp) {
		AGM_LOGE("%s Invalid handle or timestamp pointer\n", __func__);
		return -EINVAL;
	}

	return session_obj_get_timestamp(handle, timestamp);
}
