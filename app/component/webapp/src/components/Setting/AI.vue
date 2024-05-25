<template>
  <div>
    <div style="margin-bottom: 20px;">
      <el-form ref="formAiRef" :rules="formAiRules" :model="formAi" label-width="100px" label-position="left" size="mini">
        <el-form-item label="Camera:">
          <el-select v-model="formAi.src_id" @change="onChangeSrcID" :disabled="dual_mode == 0">
            <el-option v-for="item in Array.from({length:2},(item, index)=> index)" :key="item" :label="''+item" :value="item"></el-option>
          </el-select>
        </el-form-item>
      </el-form>
    </div>
    <el-tabs v-model="activeName" @tab-click="handleClick">
      <el-tab-pane label="智能选项" name="options">
        <el-form ref="formAiRef" :rules="formAiRules" :model="formAi" label-width="100px" label-position="left" size="mini">
          <el-form-item label="智能开启:">
            <el-switch v-model="formAi.ai_attr.ai_enable"></el-switch>
          </el-form-item>
          <!-- <el-form-item label="智能模式:">
            <el-select v-model="formAi.ai_attr.detect_model" :disabled="true">
              <el-option v-for="item in detect_modes" :key="item.label" :label="formAi.ai_attr.detect_only ? item.label + '（无推图）' : item.label":value="item.value"> </el-option>
            </el-select>
          </el-form-item>
          <el-form-item label="检测帧率:">
            <el-select v-model="formAi.ai_attr.detect_fps">
              <el-option v-for="item in Array.from({length:15},(item, index)=> index+1)" :key="item" :label="''+item" :value="item"> </el-option>
            </el-select>
          </el-form-item-->
          <el-form-item label="推图策略:" v-show="formAi.ai_attr.ai_enable">
            <el-select v-model="formAi.ai_attr.push_strategy.push_mode">
              <el-option v-for="item in push_strategy_options" :key="item.label" :label="item.label" :value="item.value"> </el-option>
            </el-select>
          </el-form-item>
          <el-form-item label="" v-show="formAi.ai_attr.ai_enable && (formAi.ai_attr.push_strategy.push_mode == 'FAST' || formAi.ai_attr.push_strategy.push_mode == 'INTERVAL')" >
            <el-form-item label="间隔时间(ms)">
              <el-select v-model="formAi.ai_attr.push_strategy.push_interval">
                <el-option v-for="item in push_interval_options" :key="item.label" :label="item.label" :value="item.value"> </el-option>
              </el-select>
            </el-form-item>
          </el-form-item>
          <el-form-item label="" v-show="formAi.ai_attr.ai_enable && (formAi.ai_attr.push_strategy.push_mode == 'FAST' || formAi.ai_attr.push_strategy.push_mode == 'INTERVAL')" >
            <el-form-item label="推图数量">
              <el-select v-model="formAi.ai_attr.push_strategy.push_count">
                <el-option v-for="item in Array.from({length:5},(item, index)=> index+1)" :key="item" :label="''+item" :value="item"> </el-option>
              </el-select>
            </el-form-item>
          </el-form-item>
          <!-- el-form-item label="同帧推图:">
            <el-switch v-model="formAi.ai_attr.push_strategy.push_same_frame"></el-switch>
          </el-form-item> -->
          <el-form-item label="人形防曝光:" v-show="formAi.ai_attr.ai_enable">
            <el-switch v-model="formAi.ai_attr.body_roi.enable"></el-switch>
          </el-form-item>
          <el-form-item label="" v-show="formAi.ai_attr.ai_enable && formAi.ai_attr.body_roi.enable" >
            <el-form-item label="人形最小宽度">
              <el-slider v-model="formAi.ai_attr.body_roi.min_width" :min="10" :max="1000" show-input></el-slider>
            </el-form-item>
          </el-form-item>
          <el-form-item label="" v-show="formAi.ai_attr.ai_enable && formAi.ai_attr.body_roi.enable" >
            <el-form-item label="人形最小高度">
              <el-slider v-model="formAi.ai_attr.body_roi.min_height" :min="10" :max="1000" show-input></el-slider>
            </el-form-item>
          </el-form-item>
          <el-form-item label="智能编码:" v-show="formAi.ai_attr.ai_enable && formAi.ai_attr.svc.valid">
            <el-switch v-model="formAi.ai_attr.svc.enable"></el-switch>
          </el-form-item>
          <el-form-item label="" label-width="100px" v-show="formAi.ai_attr.ai_enable && formAi.ai_attr.svc.enable">
            <el-form-item label="同步模式:" v-show="formAi.ai_attr.ai_enable && formAi.ai_attr.svc.enable && formAi.ai_attr.svc.sync_valid" class="inline">
              <el-switch v-model="formAi.ai_attr.svc.sync_mode"></el-switch>
            </el-form-item>
          </el-form-item>
          <el-form-item label="" label-width="100px" v-show="formAi.ai_attr.ai_enable && formAi.ai_attr.svc.enable">
            <el-row>
              <el-form-item label="背景Qp:" class="inline">
                <div width="100px" class="inline">
                </div>
              </el-form-item>
              <el-form-item label="iQp:" class="inline">
                <div id="bg_iQp">
                  <el-input-number controls-position="right" :min="-31" :max="32" v-model="formAi.ai_attr.svc.bg_qp.iQp" style="width:91%" :disabled="false" size="mini"></el-input-number>
                </div>
              </el-form-item>
              <el-form-item label="pQp:" class="inline-margin">
                <div id="bg_pQp">
                  <el-input-number controls-position="right" :min="-31" :max="32" v-model="formAi.ai_attr.svc.bg_qp.pQp" style="width:91%" :disabled="false" size="mini"></el-input-number>
                </div>
              </el-form-item>
            </el-row>
          </el-form-item>
          <el-form-item label="" label-width="100px" v-show="formAi.ai_attr.ai_enable && formAi.ai_attr.svc.enable">
            <el-row>
              <el-form-item label="人脸:" class="inline">
                <el-switch v-model="formAi.ai_attr.svc.face.enable"></el-switch>
              </el-form-item>
              <el-form-item label="iQp:" class="inline" v-show="formAi.ai_attr.svc.face.enable">
                <div id="face_iQp">
                  <el-input-number controls-position="right" :min="-31" :max="32" v-model="formAi.ai_attr.svc.face.qp.iQp" style="width:91%" :disabled="false" size="mini"></el-input-number>
                </div>
              </el-form-item>
              <el-form-item label="pQp:" class="inline-margin" v-show="formAi.ai_attr.svc.face.enable">
                <div id="face_pQp">
                  <el-input-number controls-position="right" :min="-31" :max="32" v-model="formAi.ai_attr.svc.face.qp.pQp" style="width:91%" :disabled="false" size="mini"></el-input-number>
                </div>
              </el-form-item>
            </el-row>
          </el-form-item>
          <el-form-item label="" label-width="100px" v-show="formAi.ai_attr.ai_enable && formAi.ai_attr.svc.enable">
            <el-row>
              <el-form-item label="人形:" class="inline">
                <el-switch v-model="formAi.ai_attr.svc.body.enable"></el-switch>
              </el-form-item>
              <el-form-item label="iQp:" class="inline" v-show="formAi.ai_attr.svc.body.enable">
                <div id="body_iQp">
                  <el-input-number controls-position="right" :min="-31" :max="32" v-model="formAi.ai_attr.svc.body.qp.iQp" style="width:91%" :disabled="false" size="mini"></el-input-number>
                </div>
              </el-form-item>
              <el-form-item label="pQp:" class="inline-margin" v-show="formAi.ai_attr.svc.body.enable">
                <div id="body_pQp">
                  <el-input-number controls-position="right" :min="-31" :max="32" v-model="formAi.ai_attr.svc.body.qp.pQp" style="width:91%" :disabled="false" size="mini"></el-input-number>
                </div>
              </el-form-item>
            </el-row>
          </el-form-item>
          <el-form-item label="" label-width="100px" v-show="formAi.ai_attr.ai_enable && formAi.ai_attr.svc.enable">
            <el-row>
              <el-form-item label="机动车:" class="inline">
                <el-switch v-model="formAi.ai_attr.svc.vehicle.enable"></el-switch>
              </el-form-item>
              <el-form-item label="iQp:" class="inline" v-show="formAi.ai_attr.svc.vehicle.enable">
                <div id="vehicle_iQp">
                  <el-input-number controls-position="right" :min="-31" :max="32" v-model="formAi.ai_attr.svc.vehicle.qp.iQp" style="width:91%" :disabled="false" size="mini"></el-input-number>
                </div>
              </el-form-item>
              <el-form-item label="pQp:" class="inline-margin" v-show="formAi.ai_attr.svc.vehicle.enable">
                <div id="vehicle_pQp">
                  <el-input-number controls-position="right" :min="-31" :max="32" v-model="formAi.ai_attr.svc.vehicle.qp.pQp" style="width:91%" :disabled="false" size="mini"></el-input-number>
                </div>
              </el-form-item>
            </el-row>
          </el-form-item>
          <el-form-item label="" label-width="100px" v-show="formAi.ai_attr.ai_enable && formAi.ai_attr.svc.enable">
            <el-row>
              <el-form-item label="非机动车:" class="inline">
                <el-switch v-model="formAi.ai_attr.svc.cycle.enable"></el-switch>
              </el-form-item>
              <el-form-item label="iQp:" class="inline" v-show="formAi.ai_attr.svc.cycle.enable">
                <div id="cycle_iQp">
                  <el-input-number controls-position="right" :min="-31" :max="32" v-model="formAi.ai_attr.svc.cycle.qp.iQp" style="width:91%" :disabled="false" size="mini"></el-input-number>
                </div>
              </el-form-item>
              <el-form-item label="pQp:" class="inline-margin" v-show="formAi.ai_attr.svc.cycle.enable">
                <div id="cycle_pQp">
                  <el-input-number controls-position="right" :min="-31" :max="32" v-model="formAi.ai_attr.svc.cycle.qp.pQp" style="width:91%" :disabled="false" size="mini"></el-input-number>
                </div>
              </el-form-item>
            </el-row>
          </el-form-item>
          <el-form-item label="" label-width="100px" v-show="formAi.ai_attr.ai_enable && formAi.ai_attr.svc.enable">
            <el-row>
              <el-form-item label="车牌:" class="inline">
                <el-switch v-model="formAi.ai_attr.svc.plate.enable"></el-switch>
              </el-form-item>
              <el-form-item label="iQp:" class="inline" v-show="formAi.ai_attr.svc.plate.enable">
                <div id="plate_iQp">
                  <el-input-number controls-position="right" :min="-31" :max="32" v-model="formAi.ai_attr.svc.plate.qp.iQp" style="width:91%" :disabled="false" size="mini"></el-input-number>
                </div>
              </el-form-item>
              <el-form-item label="pQp:" class="inline-margin" v-show="formAi.ai_attr.svc.plate.enable">
                <div id="plate_pQp">
                  <el-input-number controls-position="right" :min="-31" :max="32" v-model="formAi.ai_attr.svc.plate.qp.pQp" style="width:91%" :disabled="false" size="mini"></el-input-number>
                </div>
              </el-form-item>
            </el-row>
          </el-form-item>
        </el-form>
      </el-tab-pane>
      <el-tab-pane label="事件上报" name="events">
        <el-form ref="formAiRef" :rules="formAiRules" :model="formAi" label-width="150px" label-position="left" size="mini">
          <el-form-item label="移动侦测:">
            <el-switch v-model="formAi.ai_attr.events.motion_detect.enable"></el-switch>
            <el-form-item label="Y阈值(1-255)" v-show="formAi.ai_attr.events.motion_detect.enable">
              <el-slider v-model="formAi.ai_attr.events.motion_detect.threshold_y" :min="1" :max="255" show-input></el-slider>
            </el-form-item>
            <el-form-item label="置信度(1-100)" v-show="formAi.ai_attr.events.motion_detect.enable">
              <el-slider v-model="formAi.ai_attr.events.motion_detect.confidence" :min="1" :max="100" show-input></el-slider>
            </el-form-item>
          </el-form-item>
          <el-form-item label="遮挡侦测:">
            <el-switch v-model="formAi.ai_attr.events.occlusion_detect.enable"></el-switch>
            <el-form-item label="Y阈值(1-255):" v-show="formAi.ai_attr.events.occlusion_detect.enable">
              <el-slider v-model="formAi.ai_attr.events.occlusion_detect.threshold_y" :min="1" :max="255" show-input></el-slider>
            </el-form-item>
            <el-form-item label="置信度(1-100):" v-show="formAi.ai_attr.events.occlusion_detect.enable">
              <el-slider v-model="formAi.ai_attr.events.occlusion_detect.confidence" :min="1" :max="100" show-input></el-slider>
            </el-form-item>
          </el-form-item>
          <el-form-item label="场景切换:">
            <el-switch v-model="formAi.ai_attr.events.scene_change_detect.enable"></el-switch>
            <el-form-item label="阈值(1-100):" v-show="formAi.ai_attr.events.scene_change_detect.enable">
              <el-slider v-model="formAi.ai_attr.events.scene_change_detect.threshold_y" :min="1" :max="100" show-input></el-slider>
            </el-form-item>
            <el-form-item label="置信度(1-100):" v-show="formAi.ai_attr.events.scene_change_detect.enable">
              <el-slider v-model="formAi.ai_attr.events.scene_change_detect.confidence" :min="1" :max="100" show-input></el-slider>
            </el-form-item>
          </el-form-item>
        </el-form>
      </el-tab-pane>
      <!-- <el-tab-pane label="脸人配置" name="facehuman" :disabled="formAi.ai_attr.detect_model == 'hvcfp'">
        <el-form ref="formAiRef" :rules="formAiRules" :model="formAi" label-width="100px" label-position="left" size="mini">
          <el-row>
            <el-col :span="9">
              <el-form-item label="人脸检测:" v-show="formAi.ai_attr.detect_only == false">
                <el-switch v-model="formAi.ai_attr.facehuman.face_detect.enable"></el-switch>
              </el-form-item>
            </el-col>
            <el-col :span="9">
              <el-form-item label="人脸画框:">
                <el-switch v-model="formAi.ai_attr.facehuman.face_detect.draw_rect"></el-switch>
              </el-form-item>
            </el-col>
          </el-row>
          <el-row>
            <el-col :span="9">
              <el-form-item label="人形检测:" v-show="formAi.ai_attr.detect_only == false">
                <el-switch v-model="formAi.ai_attr.facehuman.body_detect.enable"></el-switch>
              </el-form-item>
            </el-col>
            <el-col :span="9">
              <el-form-item label="人形画框:">
                <el-switch v-model="formAi.ai_attr.facehuman.body_detect.draw_rect"></el-switch>
              </el-form-item>
            </el-col>
          </el-row>
          <el-row>
            <el-col :span="9">
              <el-form-item label="人脸识别:" v-show="formAi.ai_attr.detect_only == false">
               <el-switch v-model="formAi.ai_attr.facehuman.face_identify.enable"></el-switch>
              </el-form-item>
            </el-col>
          </el-row>
        </el-form>
      </el-tab-pane>
      <el-tab-pane label="结构化配置" name="hvcfp" :disabled="formAi.ai_attr.detect_model == 'facehuman'">
        <el-form ref="formAiRef" :rules="formAiRules" :model="formAi" label-width="100px" label-position="left" size="mini">
          <el-row>
            <el-col :span="9">
              <el-form-item label="人脸检测:" v-show="formAi.ai_attr.detect_only == false">
                <el-switch v-model="formAi.ai_attr.hvcfp.face_detect.enable"></el-switch>
              </el-form-item>
            </el-col>
            <el-col :span="9">
              <el-form-item label="人脸画框:">
                <el-switch v-model="formAi.ai_attr.hvcfp.face_detect.draw_rect"></el-switch>
              </el-form-item>
            </el-col>
          </el-row>
          <el-row>
            <el-col :span="9">
              <el-form-item label="人形检测:" v-show="formAi.ai_attr.detect_only == false">
                <el-switch v-model="formAi.ai_attr.hvcfp.body_detect.enable"></el-switch>
              </el-form-item>
            </el-col>
            <el-col :span="9">
              <el-form-item label="人形画框:">
                <el-switch v-model="formAi.ai_attr.hvcfp.body_detect.draw_rect"></el-switch>
              </el-form-item>
            </el-col>
          </el-row>
          <el-row>
            <el-col :span="9">
              <el-form-item label="机动车检测:" v-show="formAi.ai_attr.detect_only == false">
                <el-switch v-model="formAi.ai_attr.hvcfp.vechicle_detect.enable"></el-switch>
              </el-form-item>
            </el-col>
            <el-col :span="9">
              <el-form-item label="机动车画框:">
                <el-switch v-model="formAi.ai_attr.hvcfp.vechicle_detect.draw_rect"></el-switch>
              </el-form-item>
            </el-col>
          </el-row>
          <el-row>
            <el-col :span="9">
              <el-form-item label="非机动车检测:" v-show="formAi.ai_attr.detect_only == false">
                <el-switch v-model="formAi.ai_attr.hvcfp.cycle_detect.enable"></el-switch>
              </el-form-item>
            </el-col>
            <el-col :span="9">
              <el-form-item label="非机动车画框:">
                <el-switch v-model="formAi.ai_attr.hvcfp.cycle_detect.draw_rect"></el-switch>
              </el-form-item>
            </el-col>
          </el-row>
          <el-row>
            <el-col :span="9">
              <el-form-item label="车牌检测:" v-show="formAi.ai_attr.detect_only == false">
                <el-switch v-model="formAi.ai_attr.hvcfp.plate_detect.enable"></el-switch>
              </el-form-item>
            </el-col>
            <el-col :span="9">
              <el-form-item label="车牌画框:">
                <el-switch v-model="formAi.ai_attr.hvcfp.plate_detect.draw_rect"></el-switch>
              </el-form-item>
            </el-col>
          </el-row>
          <el-row>
            <el-col :span="9">
              <el-form-item label="车牌识别:" v-show="formAi.ai_attr.detect_only == false">
               <el-switch v-model="formAi.ai_attr.hvcfp.plate_identify.enable"></el-switch>
              </el-form-item>
            </el-col>
          </el-row>
        </el-form>
      </el-tab-pane>
      <el-tab-pane label="事件上报" name="events">
        <el-form ref="formAiRef" :rules="formAiRules" :model="formAi" label-width="100px" label-position="left" size="mini">
          <el-form-item label="移动侦测:">
            <el-switch v-model="formAi.ai_attr.events.motion_detect.enable"></el-switch>
            <el-form-item label="Y阈值(1-255)" v-show="formAi.ai_attr.events.motion_detect.enable">
              <el-slider v-model="formAi.ai_attr.events.motion_detect.threshold_y" :min="1" :max="255" show-input></el-slider>
            </el-form-item>
            <el-form-item label="置信度(1-100)" v-show="formAi.ai_attr.events.motion_detect.enable">
              <el-slider v-model="formAi.ai_attr.events.motion_detect.confidence" :min="1" :max="100" show-input></el-slider>
            </el-form-item>
          </el-form-item>
          <el-form-item label="遮挡侦测:">
            <el-switch v-model="formAi.ai_attr.events.occlusion_detect.enable"></el-switch>
            <el-form-item label="Y阈值(1-255)" v-show="formAi.ai_attr.events.occlusion_detect.enable">
              <el-slider v-model="formAi.ai_attr.events.occlusion_detect.threshold_y" :min="1" :max="255" show-input></el-slider>
            </el-form-item>
            <el-form-item label="置信度(1-100)" v-show="formAi.ai_attr.events.occlusion_detect.enable">
              <el-slider v-model="formAi.ai_attr.events.occlusion_detect.confidence" :min="1" :max="100" show-input></el-slider>
            </el-form-item>
          </el-form-item>
          <el-form-item label="场景切换:">
            <el-switch v-model="formAi.ai_attr.events.scene_change_detect.enable"></el-switch>
            <el-form-item label="阈值(1-100)" v-show="formAi.ai_attr.events.scene_change_detect.enable">
              <el-slider v-model="formAi.ai_attr.events.scene_change_detect.threshold_y" :min="1" :max="100" show-input></el-slider>
            </el-form-item>
            <el-form-item label="置信度(1-100)" v-show="formAi.ai_attr.events.scene_change_detect.enable">
              <el-slider v-model="formAi.ai_attr.events.scene_change_detect.confidence" :min="1" :max="100" show-input></el-slider>
            </el-form-item>
          </el-form-item>
        </el-form>
      </el-tab-pane> -->
    </el-tabs>
    <div style="margin-bottom: 20px;">
      <el-divider></el-divider>
      <el-button type="primary" @click="onSubmit" size="mini">修改</el-button>
    </div>
  </div>
</template>

<script>
export default {
  props:["dual_mode"],
  data () {
    return {
      activeName: 'options',
      detect_modes: [
        {
          label: '脸人模式',
          value: 'facehuman'
        },
        {
          label: '结构化模式',
          value: 'hvcfp'
        }
      ],
      push_strategy_options: [
        {
          label: '最快推图',
          value: 'FAST'
        },
        {
          label: '间隔推图',
          value: 'INTERVAL'
        },
        {
          label: '最优推图',
          value: 'BEST_FRAME'
        }
      ],
      push_interval_options: [
        {
          label: '1000',
          value: 1000
        },
        {
          label: '2000',
          value: 2000
        },
        {
          label: '3000',
          value: 3000
        },
        {
          label: '5000',
          value: 5000
        },
        {
          label: '10000',
          value: 10000
        },
        {
          label: '20000',
          value: 20000
        }
      ],
      formAi: {
        src_id: 0,
        ai_attr: {
          ai_enable: true,
          detect_model: 'hvcfp',
          detect_fps:15,
          push_strategy: {
            push_mode: 'BEST_FRAME',
            push_interval: 2000,
            push_count: 1,
            push_same_frame: true
          },
          detect_only: false,
          facehuman: {
            face_detect: {
              enable: true,
              draw_rect: true
            },
            body_detect: {
              enable: true,
              draw_rect: true
            },
            face_identify: {
              enable: true
            }
          },
          hvcfp: {
            face_detect: {
              enable: true,
              draw_rect: true
            },
            body_detect: {
              enable: true,
              draw_rect: true
            },
            vechicle_detect: {
              enable: true,
              draw_rect: true
            },
            cycle_detect: {
              enable: true,
              draw_rect: true
            },
            plate_detect: {
              enable: true,
              draw_rect: true
            },
            plate_identify: {
              enable: true
            }
          },
          events: {
            motion_detect: {
              enable: true,
              threshold_y: 50,
              confidence: 80
            },
            occlusion_detect: {
              enable: true,
              threshold_y: 100,
              confidence: 80
            },
            scene_change_detect: {
              enable: false,
              threshold_y: 60,
              confidence: 60
            }
          },
          body_roi: {
            enable: false,
            min_width: 100,
            min_height: 100,
            mode: 1
          },
          svc: {
            valid: false,
            sync_valid: false,
            enable: false,
            sync_mode: false,
            bg_qp: {
              iQp: 0,
              pQp: 0
            },
            body: {
              enable: false,
              qp: {
                iQp: 0,
                pQp: 0
              }
            },
            vehicle: {
              enable: false,
              qp: {
                iQp: 0,
                pQp: 0
              }
            },
            cycle: {
              enable: false,
              qp: {
                iQp: 0,
                pQp: 0
              }
            },
            face: {
              enable: false,
              qp: {
                iQp: 0,
                pQp: 0
              }
            },
            plate: {
              enable: false,
              qp: {
                iQp: 0,
                pQp: 0
              }
            }
          }
        }
      },
      formAiRules: {
        // pending
      }
    }
  },
  created () {
    console.log('ai++')
    this.getInfo()
  },
  methods: {
    handleClick(tab, event) {
      // console.log(tab, event);
    },
    onSubmit () {
      this.$refs.formAiRef.validate(async valid => {
        if (!valid) return false
        try {
          const { data: res } = await this.$http.post('setting/ai', this.formAi)
          console.log('ai post return: ', res)
          if (res.meta.status === 200) {
            this.$message.success('修改成功')
          } else {
            this.$message.error('修改失败')
          }
        } catch (error) {
          this.$message.error('修改失败')
        }
      })
    },
    async getInfo () {
      try {
        const { data: res } = await this.$http.get('setting/ai', {params:{src_id: this.formAi.src_id}})
        console.log('ai get return: ', res)
        if (res.meta.status === 200) {
          this.formAi.ai_attr.ai_enable = res.data.ai_attr.ai_enable
          this.formAi.ai_attr.detect_model = res.data.ai_attr.detect_model
          this.formAi.ai_attr.detect_fps = res.data.ai_attr.detect_fps
          this.formAi.ai_attr.push_strategy.push_mode = res.data.ai_attr.push_strategy.push_mode
          this.formAi.ai_attr.push_strategy.push_interval = res.data.ai_attr.push_strategy.push_interval
          this.formAi.ai_attr.push_strategy.push_count = res.data.ai_attr.push_strategy.push_count
          this.formAi.ai_attr.push_strategy.push_same_frame = res.data.ai_attr.push_strategy.push_same_frame

          this.formAi.ai_attr.detect_only = res.data.ai_attr.detect_only
          if (this.formAi.ai_attr.detect_model === 'facehuman') {
            this.formAi.ai_attr.facehuman.face_detect.enable = res.data.ai_attr.facehuman.face_detect.enable
            this.formAi.ai_attr.facehuman.face_detect.draw_rect = res.data.ai_attr.facehuman.face_detect.draw_rect
            this.formAi.ai_attr.facehuman.body_detect.enable = res.data.ai_attr.facehuman.body_detect.enable
            this.formAi.ai_attr.facehuman.body_detect.draw_rect = res.data.ai_attr.facehuman.body_detect.draw_rect
            this.formAi.ai_attr.facehuman.face_identify.enable = res.data.ai_attr.facehuman.face_identify.enable
          } else {
            this.formAi.ai_attr.hvcfp.face_detect.enable = res.data.ai_attr.hvcfp.face_detect.enable
            this.formAi.ai_attr.hvcfp.face_detect.draw_rect = res.data.ai_attr.hvcfp.face_detect.draw_rect
            this.formAi.ai_attr.hvcfp.body_detect.enable = res.data.ai_attr.hvcfp.body_detect.enable
            this.formAi.ai_attr.hvcfp.body_detect.draw_rect = res.data.ai_attr.hvcfp.body_detect.draw_rect
            this.formAi.ai_attr.hvcfp.vechicle_detect.enable = res.data.ai_attr.hvcfp.vechicle_detect.enable
            this.formAi.ai_attr.hvcfp.vechicle_detect.draw_rect = res.data.ai_attr.hvcfp.vechicle_detect.draw_rect
            this.formAi.ai_attr.hvcfp.cycle_detect.enable = res.data.ai_attr.hvcfp.cycle_detect.enable
            this.formAi.ai_attr.hvcfp.cycle_detect.draw_rect = res.data.ai_attr.hvcfp.cycle_detect.draw_rect
            this.formAi.ai_attr.hvcfp.plate_detect.enable = res.data.ai_attr.hvcfp.plate_detect.enable
            this.formAi.ai_attr.hvcfp.plate_detect.draw_rect = res.data.ai_attr.hvcfp.plate_detect.draw_rect
            this.formAi.ai_attr.hvcfp.plate_identify.enable = res.data.ai_attr.hvcfp.plate_identify.enable
          }

          this.formAi.ai_attr.events.motion_detect.enable = res.data.ai_attr.events.motion_detect.enable
          this.formAi.ai_attr.events.motion_detect.threshold_y = res.data.ai_attr.events.motion_detect.threshold_y
          this.formAi.ai_attr.events.motion_detect.confidence = res.data.ai_attr.events.motion_detect.confidence
          this.formAi.ai_attr.events.occlusion_detect.enable = res.data.ai_attr.events.occlusion_detect.enable
          this.formAi.ai_attr.events.occlusion_detect.threshold_y = res.data.ai_attr.events.occlusion_detect.threshold_y
          this.formAi.ai_attr.events.occlusion_detect.confidence = res.data.ai_attr.events.occlusion_detect.confidence
          this.formAi.ai_attr.events.scene_change_detect.enable = res.data.ai_attr.events.scene_change_detect.enable
          this.formAi.ai_attr.events.scene_change_detect.threshold_y = res.data.ai_attr.events.scene_change_detect.threshold_y
          this.formAi.ai_attr.events.scene_change_detect.confidence = res.data.ai_attr.events.scene_change_detect.confidence

          this.formAi.ai_attr.body_roi.enable = res.data.ai_attr.body_roi.enable
          this.formAi.ai_attr.body_roi.min_width = res.data.ai_attr.body_roi.min_width
          this.formAi.ai_attr.body_roi.min_height = res.data.ai_attr.body_roi.min_height
          this.formAi.ai_attr.body_roi.mode = res.data.ai_attr.body_roi.mode

          this.formAi.ai_attr.svc.valid = res.data.ai_attr.svc.valid
          this.formAi.ai_attr.svc.sync_valid = res.data.ai_attr.svc.sync_valid
          this.formAi.ai_attr.svc.enable = res.data.ai_attr.svc.enable
          this.formAi.ai_attr.svc.sync_mode = res.data.ai_attr.svc.sync_mode
          this.formAi.ai_attr.svc.bg_qp.iQp = res.data.ai_attr.svc.bg_qp.iQp
          this.formAi.ai_attr.svc.bg_qp.pQp = res.data.ai_attr.svc.bg_qp.pQp
          this.formAi.ai_attr.svc.body.enable = res.data.ai_attr.svc.body.enable
          this.formAi.ai_attr.svc.body.qp.iQp = res.data.ai_attr.svc.body.qp.iQp
          this.formAi.ai_attr.svc.body.qp.pQp = res.data.ai_attr.svc.body.qp.pQp
          this.formAi.ai_attr.svc.vehicle.enable = res.data.ai_attr.svc.vehicle.enable
          this.formAi.ai_attr.svc.vehicle.qp.iQp = res.data.ai_attr.svc.vehicle.qp.iQp
          this.formAi.ai_attr.svc.vehicle.qp.pQp = res.data.ai_attr.svc.vehicle.qp.pQp
          this.formAi.ai_attr.svc.cycle.enable = res.data.ai_attr.svc.cycle.enable
          this.formAi.ai_attr.svc.cycle.qp.iQp = res.data.ai_attr.svc.cycle.qp.iQp
          this.formAi.ai_attr.svc.cycle.qp.pQp = res.data.ai_attr.svc.cycle.qp.pQp
          this.formAi.ai_attr.svc.face.enable = res.data.ai_attr.svc.face.enable
          this.formAi.ai_attr.svc.face.qp.iQp = res.data.ai_attr.svc.face.qp.iQp
          this.formAi.ai_attr.svc.face.qp.pQp = res.data.ai_attr.svc.face.qp.pQp
          this.formAi.ai_attr.svc.plate.enable = res.data.ai_attr.svc.plate.enable
          this.formAi.ai_attr.svc.plate.qp.iQp = res.data.ai_attr.svc.plate.qp.iQp
          this.formAi.ai_attr.svc.plate.qp.pQp = res.data.ai_attr.svc.plate.qp.pQp
        }
      } catch (error) {
        console.log('ai getInfo got exception: ', error)
        this.$message.error('获取信息失败')
      }
    },
    onChangeSrcID() {
      this.getInfo()
    }
  }
}
</script>

<style lang="less" scoped>
.el-form {
  width: 800px!important;
}
.el-input {
  width: 100%!important;
}
.el-select {
  width: 110px!important;
}
.el-select-dropdown__item {
  text-align: center;
}
.inline {
  display: inline-block;
  width: 30%
}
.inline-margin {
  display: inline-block;
  width: 30%;
  margin-left: 20px;
}
.el-form-item {
  margin-bottom: 5px;
}
</style>
