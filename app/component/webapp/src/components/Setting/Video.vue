<template>
  <div>
    <div class="video-preview-container"></div>
    <div>
      <el-form ref="formVideoRef" :rules="formVideoRules" :model="formVideo" label-width="110px" size="mini">
        <el-form-item label="Camera:">
          <div id="cam_opt" >
            <el-select v-model="formVideo.videoFormat.src_id" @change="onChangeSrcID" :disabled="dual_mode == 0" size="mini">
              <div id="cam_opt_content" >
                <el-option v-for="item in formVideo.video_src_opts" :key="item.value" :label="item.label" :value="item.value"></el-option>
              </div>
            </el-select>
          </div>
        </el-form-item>
        <el-form-item label="启用主码流0" class="inline" v-show="formVideo.cap_list[0] > 0">
          <el-switch v-model="formVideo.videoFormat.video0.enable_stream"></el-switch>
        </el-form-item>
        <el-form-item label="" label-width="50px" v-show="formVideo.cap_list[0] > 0 && formVideo.videoFormat.video0.enable_stream" >
          <el-form-item label="编码类型:" class="inline">
            <div id="rc_encoder_type_0">
              <el-select v-model="formVideo.videoFormat.video0.encoder_type" style="width:91%" @change="onChangeEncRcType(0)" size="mini">
                <div id="rc_encoder_type_content_0">
                  <el-option v-for="item in formVideo.encode_opts" :key="item.label" :label="item.label" :value="item.value"> </el-option>
                </div>
              </el-select>
            </div>
          </el-form-item>
          <el-form-item label="码率(kbps):" class="inline">
            <el-input-number controls-position="right" :min="500" :max="15000" :step="500" v-model="formVideo.videoFormat.video0.bit_rate" style="width:91%" :disabled="formVideo.videoFormat.video0.rc_type >= 2" size="mini"></el-input-number>
          </el-form-item>
          <el-row>
            <el-form-item label="分辨率:" class="inline">
              <div id="resolution_opt_0" >
                <el-select v-model="formVideo.videoFormat.video0.resolution" style="width:91%" :disabled="!formVideo.videoFormat.video0.enable_stream || !formVideo.videoFormat.video0.enable_res_chg" size="mini">
                  <div id="resolution_opt_content_0" >
                    <el-option v-for="item in formVideo.res_opt[0]" :key="item.label" :label="item.label" :value="item.value"> </el-option>
                  </div>
                </el-select>
              </div>
            </el-form-item>
            <el-form-item label="码流控制:" class="inline">
              <div id="rc_type_opt_0" v-if="formVideo.videoFormat.video0.encoder_type == '1'" >
                <el-select v-model="formVideo.videoFormat.video0.rc_type" style="width:91%" :disabled="false" @change="onChangeEncRcType(0)" size="mini">
                  <div id="rc_type_opt_content_0" >
                    <el-option v-for="item in rc_type_options_mjpeg_arr" :key="item.value" :label="item.label" :value="item.value"></el-option>
                  </div>
                </el-select>
              </div>
              <div id="rc_type_opt_0" v-else >
                <el-select v-model="formVideo.videoFormat.video0.rc_type" style="width:91%" :disabled="false" @change="onChangeEncRcType(0)" size="mini">
                  <div id="rc_type_opt_content_0" >
                    <el-option v-for="item in rc_type_options_arr" :key="item.value" :label="item.label" :value="item.value"></el-option>
                  </div>
                </el-select>
              </div>
            </el-form-item>
          </el-row>
          <el-form-item label="min_qp:" class="inline" v-show="formVideo.videoFormat.video0.rc_type != 2">
            <div id="rc_min_qp_0" >
              <el-input-number controls-position="right" :min="0" :max=formVideo.videoFormat.video0.max_qp :step="10" v-model="formVideo.videoFormat.video0.min_qp" style="width:91%" :disabled="false" @change="onChangeRcVal(0)" size="mini"></el-input-number>
            </div>
          </el-form-item>
          <el-form-item label="max_qp:" class="inline" v-show="formVideo.videoFormat.video0.rc_type != 2">
            <div id="rc_max_qp_0" >
              <el-input-number controls-position="right" :min=formVideo.videoFormat.video0.min_qp :max="51" :step="10" v-model="formVideo.videoFormat.video0.max_qp" style="width:91%" :disabled="false" @change="onChangeRcVal(0)" size="mini"></el-input-number>
            </div>
          </el-form-item>
          <el-row>
            <el-form-item label="min_iqp:" class="inline" v-show="formVideo.videoFormat.video0.rc_type != 2 && formVideo.videoFormat.video0.encoder_type != 1">
              <div id="rc_min_iqp_0">
                <el-input-number controls-position="right" :min="0" :max=formVideo.videoFormat.video0.max_iqp :step="10" v-model="formVideo.videoFormat.video0.min_iqp" style="width:91%" :disabled="false" @change="onChangeRcVal(0)" size="mini"></el-input-number>
              </div>
            </el-form-item>
            <el-form-item label="max_iqp:" class="inline" v-show="formVideo.videoFormat.video0.rc_type != 2 && formVideo.videoFormat.video0.encoder_type != 1">
              <div id="rc_max_iqp_0">
                <el-input-number controls-position="right" :min=formVideo.videoFormat.video0.min_iqp :max="51" :step="10" v-model="formVideo.videoFormat.video0.max_iqp" style="width:91%" :disabled="false" @change="onChangeRcVal(0)" size="mini"></el-input-number>
              </div>
            </el-form-item>
          </el-row>
          <el-form-item label="min_i_prop:" class="inline" v-show="(formVideo.videoFormat.video0.rc_type === 0 || formVideo.videoFormat.video0.rc_type === 4) && formVideo.videoFormat.video0.encoder_type != 1">
            <div id="rc_min_i_prop_0">
              <el-input-number controls-position="right" :min="0" :max=formVideo.videoFormat.video0.max_iprop :step="10" v-model="formVideo.videoFormat.video0.min_iprop" style="width:91%" :disabled="false" @change="onChangeRcVal(0)" size="mini"></el-input-number>
            </div>
          </el-form-item>
          <el-form-item label="max_i_prop:" class="inline" v-show="(formVideo.videoFormat.video0.rc_type === 0 || formVideo.videoFormat.video0.rc_type === 4) && formVideo.videoFormat.video0.encoder_type != 1">
            <div id="rc_max_i_prop_0">
              <el-input-number controls-position="right" :min=formVideo.videoFormat.video0.min_iprop :max="100" :step="10" v-model="formVideo.videoFormat.video0.max_iprop" style="width:91%" :disabled="false" @change="onChangeRcVal(0)" size="mini"></el-input-number>
            </div>
          </el-form-item>
        <!--el-row>
          <el-form-item label="sht_stat_time:" class="inline" v-show="formVideo.videoFormat.video0.rc_type === 4 && formVideo.videoFormat.video0.encoder_type != 1">
            <div id="sht_stat_time_0">
              <el-input-number controls-position="right" :min="1" :max="120" :step="10" v-model="formVideo.videoFormat.video0.sht_stat_time" style="width:91%" :disabled="false" @change="onChangeRcVal(0)" size="mini"></el-input-number>
            </div>
          </el-form-item>
          <el-form-item label="lt_stat_time:" class="inline" v-show="formVideo.videoFormat.video0.rc_type === 4 && formVideo.videoFormat.video0.encoder_type != 1">
            <div id="lt_stat_time_0">
              <el-input-number controls-position="right" :min="2" :max="1440" :step="10" v-model="formVideo.videoFormat.video0.lt_stat_time" style="width:91%" :disabled="false" @change="onChangeRcVal(0)" size="mini"></el-input-number>
            </div>
          </el-form-item>
        </el-row>
          <el-form-item label="lt_min_bitrate:" class="inline" v-show="formVideo.videoFormat.video0.rc_type === 4 && formVideo.videoFormat.video0.encoder_type != 1">
            <div id="lt_min_bitrate_0">
              <el-input-number controls-position="right" :min="0" :max="614400" :step="10" v-model="formVideo.videoFormat.video0.lt_min_bitrate" style="width:91%" :disabled="false" @change="onChangeRcVal(0)" size="mini"></el-input-number>
            </div>
          </el-form-item>
          <el-form-item label="lt_max_bitrate:" class="inline" v-show="formVideo.videoFormat.video0.rc_type === 4 && formVideo.videoFormat.video0.encoder_type != 1">
            <div id="lt_max_bitrate_0">
              <el-input-number controls-position="right" :min="2" :max="614400" :step="10" v-model="formVideo.videoFormat.video0.lt_max_bitrate" style="width:91%" :disabled="false" @change="onChangeRcVal(0)" size="mini"></el-input-number>
            </div>
          </el-form-item -->
        </el-form-item>
        <el-row>
          <el-form-item label="启用子码流1" class="inline" v-show="formVideo.cap_list[1] > 0">
            <el-switch v-model="formVideo.videoFormat.video1.enable_stream"></el-switch>
          </el-form-item>
        </el-row>
        <el-form-item label="" label-width="50px" v-show="formVideo.cap_list[1] > 0 && formVideo.videoFormat.video1.enable_stream">
          <el-form-item label="编码类型:" class="inline">
            <div id="rc_encoder_type_1">
              <el-select v-model="formVideo.videoFormat.video1.encoder_type" style="width:91%" @change="onChangeEncRcType(1)" size="mini">
                <div id="rc_encoder_type_content_1">
                  <el-option v-for="item in formVideo.encode_opts" :key="item.label" :label="item.label" :value="item.value"> </el-option>
                </div>
              </el-select>
            </div>
          </el-form-item>
          <el-form-item label="码率(kbps):" class="inline">
            <el-input-number controls-position="right" :min="500" :max="15000" :step="500" v-model="formVideo.videoFormat.video1.bit_rate" style="width:91%" :disabled="formVideo.videoFormat.video1.rc_type >= 2" size="mini"></el-input-number>
          </el-form-item>
          <el-row>
          <el-form-item label="分辨率:" class="inline">
            <div id="resolution_opt_1" >
              <el-select v-model="formVideo.videoFormat.video1.resolution" style="width:91%" :disabled="!formVideo.videoFormat.video1.enable_stream || !formVideo.videoFormat.video1.enable_res_chg" size="mini">
                <div id="resolution_opt_content_1" >
                  <el-option v-for="item in formVideo.res_opt[1]" :key="item.label" :label="item.label" :value="item.value"> </el-option>
                </div>
              </el-select>
            </div>
          </el-form-item>
            <el-form-item label="码流控制:" class="inline">
              <div id="rc_type_opt_1" v-if="formVideo.videoFormat.video1.encoder_type == '1'" >
                <el-select v-model="formVideo.videoFormat.video1.rc_type" style="width:91%" :disabled="false" @change="onChangeEncRcType(1)" size="mini">
                  <div id="rc_type_opt_content_1" >
                    <el-option v-for="item in rc_type_options_mjpeg_arr" :key="item.value" :label="item.label" :value="item.value"></el-option>
                  </div>
                </el-select>
              </div>
              <div id="rc_type_opt_1" v-else >
                <el-select v-model="formVideo.videoFormat.video1.rc_type" style="width:91%" :disabled="false" @change="onChangeEncRcType(1)" size="mini">
                  <div id="rc_type_opt_content_1" >
                    <el-option v-for="item in rc_type_options_arr" :key="item.value" :label="item.label" :value="item.value"></el-option>
                  </div>
                </el-select>
              </div>
            </el-form-item>
          </el-row>
          <el-form-item label="min_qp:" class="inline" v-show="formVideo.videoFormat.video1.rc_type != 2">
            <div id="rc_min_qp_1">
              <el-input-number controls-position="right" :min="0" :max=formVideo.videoFormat.video1.max_qp :step="10" v-model="formVideo.videoFormat.video1.min_qp" style="width:91%" :disabled="false" @change="onChangeRcVal(1)" size="mini"></el-input-number>
            </div>
          </el-form-item>
          <el-form-item label="max_qp:" class="inline" v-show="formVideo.videoFormat.video1.rc_type != 2">
            <div id="rc_max_qp_1">
              <el-input-number controls-position="right" :min=formVideo.videoFormat.video1.min_qp :max="51" :step="10" v-model="formVideo.videoFormat.video1.max_qp" style="width:91%" :disabled="false" @change="onChangeRcVal(1)" size="mini"></el-input-number>
            </div>
          </el-form-item>
          <el-row>
            <el-form-item label="min_iqp:" class="inline" v-show="formVideo.videoFormat.video1.rc_type != 2 && formVideo.videoFormat.video1.encoder_type != 1">
            <div id="rc_min_iqp_1">
              <el-input-number controls-position="right" :min="0" :max=formVideo.videoFormat.video1.max_iqp :step="10" v-model="formVideo.videoFormat.video1.min_iqp" style="width:91%" :disabled="false" @change="onChangeRcVal(1)" size="mini"></el-input-number>
            </div>
          </el-form-item>
            <el-form-item label="max_iqp:" class="inline" v-show="formVideo.videoFormat.video1.rc_type != 2 && formVideo.videoFormat.video1.encoder_type != 1">
            <div id="rc_max_iqp_1">
              <el-input-number controls-position="right" :min=formVideo.videoFormat.video1.min_iqp :max="51" :step="10" v-model="formVideo.videoFormat.video1.max_iqp" style="width:91%" :disabled="false" @change="onChangeRcVal(1)" size="mini"></el-input-number>
            </div>
          </el-form-item>
          </el-row>
          <el-form-item label="min_i_prop:" class="inline" v-show="(formVideo.videoFormat.video1.rc_type === 0 || formVideo.videoFormat.video1.rc_type === 4) && formVideo.videoFormat.video1.encoder_type != 1">
            <div id="rc_min_i_prop_1">
              <el-input-number controls-position="right" :min="0" :max=formVideo.videoFormat.video1.max_iprop :step="10" v-model="formVideo.videoFormat.video1.min_iprop" style="width:91%" :disabled="false" @change="onChangeRcVal(1)" size="mini"></el-input-number>
            </div>
          </el-form-item>
          <el-form-item label="max_i_prop:" class="inline" v-show="(formVideo.videoFormat.video1.rc_type === 0 || formVideo.videoFormat.video1.rc_type === 4) && formVideo.videoFormat.video1.encoder_type != 1">
            <div id="rc_max_i_prop_1">
              <el-input-number controls-position="right" :min=formVideo.videoFormat.video1.min_iprop :max="100" :step="10" v-model="formVideo.videoFormat.video1.max_iprop" style="width:91%" :disabled="false" @change="onChangeRcVal(1)" size="mini"></el-input-number>
            </div>
          </el-form-item>
          <!--el-row>
            <el-form-item label="sht_stat_time:" class="inline" v-show="formVideo.videoFormat.video1.rc_type === 4 && formVideo.videoFormat.video1.encoder_type != 1">
              <div id="sht_stat_time_1">
                <el-input-number controls-position="right" :min="1" :max="120" :step="10" v-model="formVideo.videoFormat.video1.sht_stat_time" style="width:91%" :disabled="false" @change="onChangeRcVal(1)" size="mini"></el-input-number>
              </div>
            </el-form-item>
            <el-form-item label="lt_stat_time:" class="inline" v-show="formVideo.videoFormat.video1.rc_type === 4 && formVideo.videoFormat.video1.encoder_type != 1">
              <div id="lt_stat_time_1">
                <el-input-number controls-position="right" :min="2" :max="1440" :step="10" v-model="formVideo.videoFormat.video1.lt_stat_time" style="width:91%" :disabled="false" @change="onChangeRcVal(1)" size="mini"></el-input-number>
              </div>
            </el-form-item>
          </el-row>
          <el-form-item label="lt_min_bitrate:" class="inline" v-show="formVideo.videoFormat.video1.rc_type === 4 && formVideo.videoFormat.video1.encoder_type != 1">
            <div id="lt_min_bitrate_1">
              <el-input-number controls-position="right" :min="0" :max="614400" :step="10" v-model="formVideo.videoFormat.video1.lt_min_bitrate" style="width:91%" :disabled="false" @change="onChangeRcVal(1)" size="mini"></el-input-number>
            </div>
          </el-form-item>
          <el-form-item label="lt_max_bitrate:" class="inline" v-show="formVideo.videoFormat.video1.rc_type === 4 && formVideo.videoFormat.video1.encoder_type != 1">
            <div id="lt_max_bitrate_1">
              <el-input-number controls-position="right" :min="2" :max="614400" :step="10" v-model="formVideo.videoFormat.video1.lt_max_bitrate" style="width:91%" :disabled="false" @change="onChangeRcVal(1)" size="mini"></el-input-number>
            </div>
          </el-form-item -->
        </el-form-item>
        <el-row>
          <el-form-item label="启用子码流2" class="inline" v-show="formVideo.cap_list[2] > 0">
            <el-switch v-model="formVideo.videoFormat.video2.enable_stream"></el-switch>
          </el-form-item>
        </el-row>
        <el-form-item label="" label-width="50px" v-show="formVideo.cap_list[2] > 0 && formVideo.videoFormat.video2.enable_stream">
          <el-form-item label="编码类型:" class="inline">
            <div id="rc_encoder_type_2">
              <el-select v-model="formVideo.videoFormat.video2.encoder_type" style="width:91%" @change="onChangeEncRcType(2)" size="mini">
                <div id="rc_encoder_type_content_2">
                  <el-option v-for="item in formVideo.encode_opts" :key="item.label" :label="item.label" :value="item.value"> </el-option>
                </div>
              </el-select>
            </div>
          </el-form-item>
          <el-form-item label="码率(kbps):" class="inline">
            <el-input-number controls-position="right" :min="500" :max="15000" :step="500" v-model="formVideo.videoFormat.video2.bit_rate" style="width:91%" :disabled="formVideo.videoFormat.video2.rc_type >= 2" size="mini"></el-input-number>
          </el-form-item>
          <el-row>
            <el-form-item label="分辨率:" class="inline">
              <div id="resolution_opt_2" >
                <el-select v-model="formVideo.videoFormat.video2.resolution" style="width:91%" :disabled="!formVideo.videoFormat.video2.enable_stream || !formVideo.videoFormat.video2.enable_res_chg" size="mini">
                  <div id="resolution_opt_content_2" >
                    <el-option v-for="item in formVideo.res_opt[2]" :key="item.label" :label="item.label" :value="item.value"> </el-option>
                  </div>
                </el-select>
              </div>
            </el-form-item>
            <el-form-item label="码流控制:" class="inline">
              <div id="rc_type_opt_2" v-if="formVideo.videoFormat.video2.encoder_type == '1'" >
                <el-select v-model="formVideo.videoFormat.video2.rc_type" style="width:91%" :disabled="false" @change="onChangeEncRcType(2)" size="mini">
                  <div id="rc_type_opt_content_2" >
                    <el-option v-for="item in rc_type_options_mjpeg_arr" :key="item.value" :label="item.label" :value="item.value"></el-option>
                  </div>
                </el-select>
              </div>
              <div id="rc_type_opt_2" v-else >
                <el-select v-model="formVideo.videoFormat.video2.rc_type" style="width:91%" :disabled="false" @change="onChangeEncRcType(2)" size="mini">
                  <div id="rc_type_opt_content_2" >
                    <el-option v-for="item in rc_type_options_arr" :key="item.value" :label="item.label" :value="item.value"></el-option>
                  </div>
                </el-select>
              </div>
            </el-form-item>
          </el-row>
          <el-form-item label="min_qp:" class="inline" v-show="formVideo.videoFormat.video2.rc_type != 2">
            <div id="rc_min_qp_2">
              <el-input-number controls-position="right" :min="0" :max=formVideo.videoFormat.video2.max_qp :step="10" v-model="formVideo.videoFormat.video2.min_qp" style="width:91%" :disabled="false" @change="onChangeRcVal(2)" size="mini"></el-input-number>
            </div>
          </el-form-item>
          <el-form-item label="max_qp:" class="inline" v-show="formVideo.videoFormat.video2.rc_type != 2">
            <div id="rc_max_qp_2">
              <el-input-number controls-position="right" :min=formVideo.videoFormat.video2.min_qp :max="51" :step="10" v-model="formVideo.videoFormat.video2.max_qp" style="width:91%" :disabled="false" @change="onChangeRcVal(2)" size="mini"></el-input-number>
            </div>
          </el-form-item>
          <el-row>
            <el-form-item label="min_iqp:" class="inline" v-show="formVideo.videoFormat.video2.rc_type != 2 && formVideo.videoFormat.video2.encoder_type != 1">
              <div id="rc_min_iqp_2">
                <el-input-number controls-position="right" :min="0" :max=formVideo.videoFormat.video2.max_iqp :step="10" v-model="formVideo.videoFormat.video2.min_iqp" style="width:91%" :disabled="false" @change="onChangeRcVal(2)" size="mini"></el-input-number>
              </div>
            </el-form-item>
            <el-form-item label="max_iqp:" class="inline" v-show="formVideo.videoFormat.video2.rc_type != 2 && formVideo.videoFormat.video2.encoder_type != 1">
              <div id="rc_max_iqp_2">
                <el-input-number controls-position="right" :min=formVideo.videoFormat.video2.min_iqp :max="51" :step="10" v-model="formVideo.videoFormat.video2.max_iqp" style="width:91%" :disabled="false" @change="onChangeRcVal(2)" size="mini"></el-input-number>
              </div>
            </el-form-item>
          </el-row>
          <el-form-item label="min_i_prop:" class="inline" v-show="(formVideo.videoFormat.video2.rc_type === 0 || formVideo.videoFormat.video2.rc_type === 4) && formVideo.videoFormat.video2.encoder_type != 1">
            <div id="rc_min_i_prop_2">
              <el-input-number controls-position="right" :min="0" :max=formVideo.videoFormat.video2.max_iprop :step="10" v-model="formVideo.videoFormat.video2.min_iprop" style="width:91%" :disabled="false" @change="onChangeRcVal(2)" size="mini"></el-input-number>
            </div>
          </el-form-item>
          <el-form-item label="max_i_prop:" class="inline" v-show="(formVideo.videoFormat.video2.rc_type === 0 || formVideo.videoFormat.video2.rc_type === 4) && formVideo.videoFormat.video2.encoder_type != 1">
            <div id="rc_max_i_prop_2">
              <el-input-number controls-position="right" :min=formVideo.videoFormat.video2.min_iprop :max="100" :step="10" v-model="formVideo.videoFormat.video2.max_iprop" style="width:91%" :disabled="false" @change="onChangeRcVal(2)" size="mini"></el-input-number>
            </div>
          </el-form-item>
          <!--el-row>
            <el-form-item label="sht_stat_time:" class="inline" v-show="formVideo.videoFormat.video2.rc_type === 4 && formVideo.videoFormat.video2.encoder_type != 1">
              <div id="sht_stat_time_2">
                <el-input-number controls-position="right" :min="1" :max="120" :step="10" v-model="formVideo.videoFormat.video2.sht_stat_time" style="width:91%" :disabled="false" @change="onChangeRcVal(2)" size="mini"></el-input-number>
              </div>
            </el-form-item>
            <el-form-item label="lt_stat_time:" class="inline" v-show="formVideo.videoFormat.video2.rc_type === 4 && formVideo.videoFormat.video2.encoder_type != 1">
              <div id="lt_stat_time_2">
                <el-input-number controls-position="right" :min="2" :max="1440" :step="10" v-model="formVideo.videoFormat.video2.lt_stat_time" style="width:91%" :disabled="false" @change="onChangeRcVal(2)" size="mini"></el-input-number>
              </div>
            </el-form-item>
          </el-row>
          <el-form-item label="lt_min_bitrate:" class="inline" v-show="formVideo.videoFormat.video2.rc_type === 4 && formVideo.videoFormat.video2.encoder_type != 1">
            <div id="lt_min_bitrate_2">
              <el-input-number controls-position="right" :min="0" :max="614400" :step="10" v-model="formVideo.videoFormat.video2.lt_min_bitrate" style="width:91%" :disabled="false" @change="onChangeRcVal(2)" size="mini"></el-input-number>
            </div>
          </el-form-item>
          <el-form-item label="lt_max_bitrate:" class="inline" v-show="formVideo.videoFormat.video2.rc_type === 4 && formVideo.videoFormat.video2.encoder_type != 1">
            <div id="lt_max_bitrate_2">
              <el-input-number controls-position="right" :min="2" :max="614400" :step="10" v-model="formVideo.videoFormat.video2.lt_max_bitrate" style="width:91%" :disabled="false" @change="onChangeRcVal(2)" size="mini"></el-input-number>
            </div>
          </el-form-item -->
        </el-form-item>
        <el-row>
          <el-form-item label="启用子码流3" class="inline" v-show="formVideo.cap_list[3] > 0">
            <el-switch v-model="formVideo.videoFormat.video3.enable_stream"></el-switch>
          </el-form-item>
        </el-row>
        <el-form-item label="" label-width="50px" v-show="formVideo.cap_list[3] > 0 && formVideo.videoFormat.video3.enable_stream">
          <el-form-item label="编码类型:" class="inline">
            <div id="rc_encoder_type_3">
              <el-select v-model="formVideo.videoFormat.video3.encoder_type" style="width:91%" @change="onChangeEncRcType(3)" size="mini">
                <div id="rc_encoder_type_content_3">
                  <el-option v-for="item in formVideo.encode_opts" :key="item.label" :label="item.label" :value="item.value"> </el-option>
                </div>
              </el-select>
            </div>
          </el-form-item>
          <el-form-item label="码率(kbps):" class="inline">
            <el-input-number controls-position="right" :min="500" :max="15000" :step="500" v-model="formVideo.videoFormat.video3.bit_rate" style="width:91%" :disabled="formVideo.videoFormat.video3.rc_type >= 2" size="mini"></el-input-number>
          </el-form-item>
          <el-row>
            <el-form-item label="分辨率:" class="inline">
              <div id="resolution_opt_3" >
                <el-select v-model="formVideo.videoFormat.video3.resolution" style="width:91%" :disabled="!formVideo.videoFormat.video3.enable_stream || !formVideo.videoFormat.video3.enable_res_chg" size="mini">
                  <div id="resolution_opt_content_3" >
                    <el-option v-for="item in formVideo.res_opt[3]" :key="item.label" :label="item.label" :value="item.value"> </el-option>
                  </div>
                </el-select>
              </div>
            </el-form-item>
            <el-form-item label="码流控制:" class="inline">
              <div id="rc_type_opt_3" v-if="formVideo.videoFormat.video3.encoder_type == '1'" >
                <el-select v-model="formVideo.videoFormat.video3.rc_type" style="width:91%" :disabled="false" @change="onChangeEncRcType(3)" size="mini">
                  <div id="rc_type_opt_content_3" >
                    <el-option v-for="item in rc_type_options_mjpeg_arr" :key="item.value" :label="item.label" :value="item.value"></el-option>
                  </div>
                </el-select>
              </div>
              <div id="rc_type_opt_3" v-else >
                <el-select v-model="formVideo.videoFormat.video3.rc_type" style="width:91%" :disabled="false" @change="onChangeEncRcType(3)" size="mini">
                  <div id="rc_type_opt_content_3" >
                    <el-option v-for="item in rc_type_options_arr" :key="item.value" :label="item.label" :value="item.value"></el-option>
                  </div>
                </el-select>
              </div>
            </el-form-item>
          </el-row>
          <el-form-item label="min_qp:" class="inline" v-show="formVideo.videoFormat.video3.rc_type != 2">
            <div id="rc_min_qp_3">
              <el-input-number controls-position="right" :min="0" :max=formVideo.videoFormat.video3.max_qp :step="10" v-model="formVideo.videoFormat.video3.min_qp" style="width:91%" :disabled="false" @change="onChangeRcVal(3)" size="mini"></el-input-number>
            </div>
          </el-form-item>
          <el-form-item label="max_qp:" class="inline" v-show="formVideo.videoFormat.video3.rc_type != 2">
            <div id="rc_max_qp_3">
              <el-input-number controls-position="right" :min=formVideo.videoFormat.video3.min_qp :max="51" :step="10" v-model="formVideo.videoFormat.video3.max_qp" style="width:91%" :disabled="false" @change="onChangeRcVal(3)" size="mini"></el-input-number>
            </div>
          </el-form-item>
          <el-row>
            <el-form-item label="min_iqp:" class="inline" v-show="formVideo.videoFormat.video3.rc_type != 2 && formVideo.videoFormat.video3.encoder_type != 1">
              <div id="rc_min_iqp_3">
                <el-input-number controls-position="right" :min="0" :max=formVideo.videoFormat.video3.max_iqp :step="10" v-model="formVideo.videoFormat.video3.min_iqp" style="width:91%" :disabled="false" @change="onChangeRcVal(3)" size="mini"></el-input-number>
              </div>
            </el-form-item>
            <el-form-item label="max_iqp:" class="inline" v-show="formVideo.videoFormat.video3.rc_type != 2 && formVideo.videoFormat.video3.encoder_type != 1">
              <div id="rc_max_iqp_3">
                <el-input-number controls-position="right" :min=formVideo.videoFormat.video3.min_iqp :max="51" :step="10" v-model="formVideo.videoFormat.video3.max_iqp" style="width:91%" :disabled="false" @change="onChangeRcVal(3)" size="mini"></el-input-number>
              </div>
            </el-form-item>
          </el-row>
          <el-form-item label="min_i_prop:" class="inline" v-show="(formVideo.videoFormat.video3.rc_type === 0 || formVideo.videoFormat.video3.rc_type === 4) && formVideo.videoFormat.video3.encoder_type != 1">
            <div id="rc_min_i_prop_3">
              <el-input-number controls-position="right" :min="0" :max=formVideo.videoFormat.video3.max_iprop :step="10" v-model="formVideo.videoFormat.video3.min_iprop" style="width:91%" :disabled="false" @change="onChangeRcVal(3)" size="mini"></el-input-number>
            </div>
          </el-form-item>
          <el-form-item label="max_i_prop:" class="inline" v-show="(formVideo.videoFormat.video3.rc_type === 0 || formVideo.videoFormat.video3.rc_type === 4) && formVideo.videoFormat.video3.encoder_type != 1">
            <div id="rc_max_i_prop_3">
              <el-input-number controls-position="right" :min=formVideo.videoFormat.video3.min_iprop :max="100" :step="10" v-model="formVideo.videoFormat.video3.max_iprop" style="width:91%" :disabled="false" @change="onChangeRcVal(3)" size="mini"></el-input-number>
            </div>
          </el-form-item>
          <!-- el-row>
          <el-form-item label="sht_stat_time:" class="inline" v-show="formVideo.videoFormat.video3.rc_type === 4 && formVideo.videoFormat.video3.encoder_type != 1">
            <div id="sht_stat_time_3">
              <el-input-number controls-position="right" :min="1" :max="120" :step="10" v-model="formVideo.videoFormat.video3.sht_stat_time" style="width:91%" :disabled="false" @change="onChangeRcVal(3)" size="mini"></el-input-number>
            </div>
          </el-form-item>
          <el-form-item label="lt_stat_time:" class="inline" v-show="formVideo.videoFormat.video3.rc_type === 4 && formVideo.videoFormat.video3.encoder_type != 1">
            <div id="lt_stat_time_3">
              <el-input-number controls-position="right" :min="2" :max="1440" :step="10" v-model="formVideo.videoFormat.video3.lt_stat_time" style="width:91%" :disabled="false" @change="onChangeRcVal(3)" size="mini"></el-input-number>
            </div>
          </el-form-item>
        </el-row>
          <el-form-item label="lt_min_bitrate:" class="inline" v-show="formVideo.videoFormat.video3.rc_type === 4 && formVideo.videoFormat.video3.encoder_type != 1">
            <div id="lt_min_bitrate_3">
              <el-input-number controls-position="right" :min="0" :max="614400" :step="10" v-model="formVideo.videoFormat.video3.lt_min_bitrate" style="width:91%" :disabled="false" @change="onChangeRcVal(3)" size="mini"></el-input-number>
            </div>
          </el-form-item>
          <el-form-item label="lt_max_bitrate:" class="inline" v-show="formVideo.videoFormat.video3.rc_type === 4 && formVideo.videoFormat.video3.encoder_type != 1">
            <div id="lt_max_bitrate_3">
              <el-input-number controls-position="right" :min="2" :max="614400" :step="10" v-model="formVideo.videoFormat.video3.lt_max_bitrate" style="width:91%" :disabled="false" @change="onChangeRcVal(3)" size="mini"></el-input-number>
            </div>
          </el-form-item -->
        </el-form-item>
        <el-form-item>
          <el-divider></el-divider>
          <el-button type="primary" @click="onSubmit">修改</el-button>
        </el-form-item>
      </el-form>
    </div>
  </div>
</template>

<script>
export default {
  props: ["dual_mode"],
  data() {
    return {
      formVideo: {
        video_src_opts: [
          {
            label: '0',
            value: 0
          },
          {
            label: '1',
            value: 1
          }
        ],
        rc_type_options: [
          {
            label: 'CBR',
            value: 0
          },
          {
            label: 'VBR',
            value: 1
          },
          {
            label: 'FIXQP',
            value: 2
          },
          {
            label: 'AVBR',
            value: 3
          },
          {
            label: 'CVBR',
            value: 4
          }
        ],
        encode_opts: [
          {
            label: 'H264',
            value: 0
          },
          {
            label: 'MJPEG',
            value: 1
          },
          {
            label: 'H265',
            value: 2
          }
        ],
        res_opt: [[],[],[],[]],
        enc_rc_info: [[],[],[],[]],
        cap_list: [0, 0, 0, 0],
        videoFormat: {
          src_id: 0,
          video0: {
            enable_stream: false,
            enable_res_chg: false,
            encoder_type: 0,
            bit_rate: 0,
            resolution: '',
            resolution_opt: [],
            rc_type: 0,
            min_qp: 0,
            max_qp: 51,
            min_iqp: 0,
            max_iqp: 51,
            min_iprop: 10,
            max_iprop: 40,
            sht_stat_time: 3,
            lt_stat_time: 600,
            lt_min_bitrate: 2048,
            lt_max_bitrate: 4096
          },
          video1: {
            enable_stream: false,
            enable_res_chg: false,
            encoder_type: 0,
            bit_rate: 0,
            resolution: '',
            resolution_opt: [],
            rc_type: 0,
            min_qp: 0,
            max_qp: 51,
            min_iqp: 0,
            max_iqp: 51,
            min_iprop: 10,
            max_iprop: 40,
            sht_stat_time: 3,
            lt_stat_time: 600,
            lt_min_bitrate: 2048,
            lt_max_bitrate: 4096
          },
          video2: {
            enable_stream: false,
            enable_res_chg: false,
            encoder_type: 0,
            bit_rate: 0,
            resolution: '',
            resolution_opt: [],
            rc_type: 0,
            min_qp: 0,
            max_qp: 51,
            min_iqp: 0,
            max_iqp: 51,
            min_iprop: 10,
            max_iprop: 40,
            sht_stat_time: 3,
            lt_stat_time: 600,
            lt_min_bitrate: 2048,
            lt_max_bitrate: 4096
          },
          video3: {
            enable_stream: false,
            enable_res_chg: false,
            encoder_type: 0,
            bit_rate: 0,
            resolution: '',
            resolution_opt: [],
            rc_type: 0,
            min_qp: 0,
            max_qp: 51,
            min_iqp: 0,
            max_iqp: 51,
            min_iprop: 10,
            max_iprop: 40,
            sht_stat_time: 3,
            lt_stat_time: 600,
            lt_min_bitrate: 2048,
            lt_max_bitrate: 4096
          }
        }
      },
      rc_type_options_arr: [
        {
          label: 'CBR',
          value: 0
        },
        {
          label: 'VBR',
          value: 1
        },
        {
          label: 'FIXQP',
          value: 2
        },
        {
          label: 'AVBR',
          value: 3
        },
        {
          label: 'CVBR',
          value: 4
        }
      ],
      rc_type_options_mjpeg_arr: [
        {
          label: 'CBR',
          value: 0
        },
        {
          label: 'VBR',
          value: 1
        },
        {
          label: 'FIXQP',
          value: 2
        }
      ],
      formVideoRules: {
      }
    }
  },
  created() {
    console.log('video++')
    this.getInfo()
    console.log('video--')
  },
  methods: {
    async onSubmit() {
      try {
        var { ...videoFormat } = this.formVideo.videoFormat
        if (this.formVideo.cap_list[1] <= 0) {
          delete videoFormat.video1
        }
        if (this.formVideo.cap_list[2] <= 0) {
          delete videoFormat.video2
        }
        if (this.formVideo.cap_list[3] <= 0) {
          delete videoFormat.video3
        }

        const { data: res } = await this.$http.post('setting/video', videoFormat)
        console.log('video get return: ', res)
        if (res.meta.status === 200) {
          this.$message.success('修改成功')
        } else {
          this.$message.success('修改失败')
        }
      } catch (error) {
        this.$message.error('修改失败')
      }
    },
    async getInfo() {
      try {
        const { data: res } = await this.$http.get('setting/video', { params: { src_id: this.formVideo.videoFormat.src_id } })
        console.log('video get return: ', res)
        if (res.meta.status === 200) {
          this.formVideo.cap_list = res.data.cap_list

          if (this.formVideo.cap_list[0] > 0) {
            this.formVideo.videoFormat.video0 = res.data.video0
            this.formVideo.enc_rc_info[0] = res.data.attrVideo0
          }

          if (this.formVideo.cap_list[1] > 0) {
            this.formVideo.videoFormat.video1 = res.data.video1
            this.formVideo.enc_rc_info[1] = res.data.attrVideo1
          }

          if (this.formVideo.cap_list[2] > 0) {
            this.formVideo.videoFormat.video2 = res.data.video2
            this.formVideo.enc_rc_info[2] = res.data.attrVideo2
          }

          if (this.formVideo.cap_list[3] > 0) {
            this.formVideo.videoFormat.video3 = res.data.video3
            this.formVideo.enc_rc_info[3] = res.data.attrVideo3
          }

          this.init_resolution_options()
          this.init_rc_infos()
        }
      } catch (error) {
        console.log("video getInfo got exception: " + error)
        this.$message.error('获取信息失败')
      }
    },
    init_rc_infos() {
      try {
        let _rc_info_array = this.formVideo.enc_rc_info
        let _video_info_array = [this.formVideo.videoFormat.video0, this.formVideo.videoFormat.video1, this.formVideo.videoFormat.video2, this.formVideo.videoFormat.video3]
        for (let i = 0; i < _video_info_array.length; i++) {
          if (!_rc_info_array[i].enc_rc_info) {
            continue
          }
          for (let j = 0; j < _rc_info_array[i].enc_rc_info.length; j++) {
            let rc_info = _rc_info_array[i].enc_rc_info[j]

            if (_video_info_array[i].encoder_type == rc_info.encoder_type) {
              for (let k = 0; k < rc_info.rc.length; k++) {
                if (rc_info.rc[k].rc_type == _video_info_array[i].rc_type) {
                  _video_info_array[i].min_qp = rc_info.rc[k].min_qp
                  _video_info_array[i].max_qp = rc_info.rc[k].max_qp
                  _video_info_array[i].min_iqp = rc_info.rc[k].min_iqp
                  _video_info_array[i].max_iqp = rc_info.rc[k].max_iqp
                  _video_info_array[i].min_iprop = rc_info.rc[k].min_iprop
                  _video_info_array[i].max_iprop = rc_info.rc[k].max_iprop
                  break
                }
              }
              break
            }
          }
        }
      } catch (error) {
        console.log("init_rc_infos got exception: " + error)
      }
    },
    init_resolution_options() {
      let _video_info_array = this.formVideo.enc_rc_info
      try {
        for (var i = 0; i < _video_info_array.length; i++) {
          if(!_video_info_array[i].resolution_opt) {
            continue
          }
          this.formVideo.res_opt[i] = []
          for (var j = 0; j < _video_info_array[i].resolution_opt.length; j++) {
            var _res = _video_info_array[i].resolution_opt[j].trim() + ''
            var _item = { label: _res, value: _res }
            this.formVideo.res_opt[i].push(_item)
          }
        }
      } catch (error) {
        console.log("init_resolution_options got exception: " + error)
      }
    },
    onChangeSrcID() {
      this.getInfo()
    },
    onChangeEncRcType(channel) {
      let _rc_info_array = this.formVideo.enc_rc_info
      let _video_info_array = [this.formVideo.videoFormat.video0, this.formVideo.videoFormat.video1, this.formVideo.videoFormat.video2, this.formVideo.videoFormat.video3]
      try {
        if (_video_info_array[channel].encoder_type == 1 && (_video_info_array[channel].rc_type == 3 || _video_info_array[channel].rc_type == 4)) {
          _video_info_array[channel].rc_type = 0
        }
        for (let j = 0; j < _rc_info_array[channel].enc_rc_info.length; j++) {
          let rc_info = _rc_info_array[channel].enc_rc_info[j]
          if (_video_info_array[channel].encoder_type == rc_info.encoder_type) {
            for (let k = 0; k < rc_info.rc.length; k++) {
              if (rc_info.rc[k].rc_type == _video_info_array[channel].rc_type) {
                let _rc = rc_info.rc[k]
                _video_info_array[channel].min_qp = _rc.min_qp
                _video_info_array[channel].max_qp = _rc.max_qp

                _video_info_array[channel].min_iqp = _rc.min_iqp
                _video_info_array[channel].max_iqp = _rc.max_iqp

                _video_info_array[channel].min_iprop = _rc.min_iprop
                _video_info_array[channel].max_iprop = _rc.max_iprop

                _video_info_array[channel].sht_stat_time = _rc.sht_stat_time
                _video_info_array[channel].lt_stat_time = _rc.lt_stat_time
                _video_info_array[channel].lt_min_bitrate = _rc.lt_min_bitrate
                _video_info_array[channel].lt_max_bitrate = _rc.lt_max_bitrate
                break
              }
            }
            break
          }
        }
      } catch (error) {
        console.log("onChangeEncRcType got exception: " + error)
      }

    },
    onChangeRcVal(channel) {
      let _rc_info_array = this.formVideo.enc_rc_info
      let _video_info_array = [this.formVideo.videoFormat.video0, this.formVideo.videoFormat.video1, this.formVideo.videoFormat.video2, this.formVideo.videoFormat.video3]
      try {
        for (let j = 0; j < _rc_info_array[channel].enc_rc_info.length; j++) {
          let rc_info = _rc_info_array[channel].enc_rc_info[j]
          if (_video_info_array[channel].encoder_type == rc_info.encoder_type) {
            for (let k = 0; k < rc_info.rc.length; k++) {
              if (rc_info.rc[k].rc_type == _video_info_array[channel].rc_type) {
                let _rc = rc_info.rc[k]

                _rc.min_qp = _video_info_array[channel].min_qp
                _rc.max_qp = _video_info_array[channel].max_qp

                _rc.min_iqp = _video_info_array[channel].min_iqp
                _rc.max_iqp = _video_info_array[channel].max_iqp

                _rc.min_iprop = _video_info_array[channel].min_iprop
                _rc.max_iprop = _video_info_array[channel].max_iprop

                _rc.sht_stat_time = _video_info_array[channel].sht_stat_time
                _rc.lt_stat_time = _video_info_array[channel].lt_stat_time
                _rc.lt_min_bitrate = _video_info_array[channel].lt_min_bitrate
                _rc.lt_max_bitrate = _video_info_array[channel].lt_max_bitrate
                break
              }
            }
            break
          }
        }
      } catch (error) {
        console.log("onChangeRcVal got exception: " + error)
      }
    }
  }
}
</script>

<style lang="less" scoped>
.el-input-number {
  width: 100px;
}

.el-select {
  width: 110px;
  text-align-last: center;
}

.el-select-dropdown__item {
  text-align: center;
}


.inline {
  display: inline-block;
  width: 30%
}

.el-form-item {
  margin-bottom: 5px;
}
</style>
