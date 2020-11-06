package com.example.uploaddemo_android;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.MediaController;
import android.widget.ProgressBar;
import android.widget.TextView;
import android.widget.VideoView;

import com.luck.picture.lib.PictureSelector;
import com.luck.picture.lib.config.PictureConfig;
import com.luck.picture.lib.config.PictureMimeType;
import com.luck.picture.lib.entity.LocalMedia;
import com.qiniu.android.collect.ReportConfig;
import com.qiniu.android.common.FixedZone;
import com.qiniu.android.http.ResponseInfo;
import com.qiniu.android.http.dns.Dns;
import com.qiniu.android.http.dns.IDnsNetworkAddress;
import com.qiniu.android.storage.Configuration;
import com.qiniu.android.storage.GlobalConfiguration;
import com.qiniu.android.storage.UpCompletionHandler;
import com.qiniu.android.storage.UpProgressHandler;
import com.qiniu.android.storage.UploadManager;
import com.qiniu.android.storage.UploadOptions;

import org.json.JSONObject;

import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Map;


public class MainActivity extends AppCompatActivity {

    private TextView progressTV = null;
    private ProgressBar progressBar = null;
    private ImageView imageView = null;
    private VideoView videoView = null;
    private Button selectBtn = null;
    private Button uploadBtn = null;

    private String mediaPath = null;

    private UploadManager uploadManager = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        initData();
        initUI();
    }

    private void initUI(){
        progressTV = findViewById(R.id.upload_progress_label);
        progressBar = findViewById(R.id.upload_progress);
        imageView = findViewById(R.id.upload_image);
        videoView = findViewById(R.id.upload_video);
        videoView.getBackground().setAlpha(1);
        selectBtn = findViewById(R.id.upload_btn_select);
        uploadBtn = findViewById(R.id.upload_btn_upload);

        selectBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                selectImage();
            }
        });

        uploadBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                uploadImage();
            }
        });
    }

    private void initData(){
        ReportConfig.getInstance().isReportEnable = false;
        GlobalConfiguration.getInstance().dns = new Dns() {
            @Override
            public List<IDnsNetworkAddress> lookup(String hostname) throws UnknownHostException {
                if (!hostname.equals("up.qiniu.com")
                        && !hostname.equals("uc.qbox.me")
                        && !hostname.equals("api.qiniu.com")){
                    return null;
                }
                IDnsNetworkAddress address = new IDnsNetworkAddress() {
                    @Override
                    public String getHostValue() {
                        return "up.qiniu.com";
                    }

                    @Override
                    public String getIpValue() {
                        return "10.200.20.57";
                    }

                    @Override
                    public Long getTtlValue() {
                        return 120l;
                    }

                    @Override
                    public String getSourceValue() {
                        return "customized";
                    }

                    @Override
                    public Long getTimestampValue() {
                        return 120l;
                    }
                };
                ArrayList<IDnsNetworkAddress> list = new ArrayList<>();
                list.add(address);
                return list;
            }
        };

        FixedZone zone = new FixedZone(new String[]{"up.qiniu.com"});
        Configuration.Builder builder = new Configuration.Builder();
        builder.useHttps(false)
                .useConcurrentResumeUpload(false).concurrentTaskCount(3)
                .allowBackupHost(true)
                .zone(zone);
        uploadManager = new UploadManager(builder.build());
    }


    private void selectImage(){

        PictureSelector.create(MainActivity.this)
                .openGallery(PictureMimeType.ofAll())
                .minSelectNum(1)
                .maxSelectNum(1)
                .forResult(PictureConfig.CHOOSE_REQUEST);

    }

    private void uploadImage(){
        if (mediaPath == null){
            // 2.9M
            mediaPath = "/sdcard/thku.mp3";
            // 85.7M
//            mediaPath = "/sdcard/clock_1.flv";
        }
        if (mediaPath == null){
            showMessage("请先选择上传资源");
            return;
        }

        String token = "your token";
        token = "dxVQk8gyk3WswArbNhdKIwmwibJ9nFsQhMNUmtIM:j6i3LDn2N1GlQCKYR9eRjBYgytk=:eyJzY29wZSI6ImtvZG8tcGhvbmUtem9uZTAtc3BhY2UiLCJkZWFkbGluZSI6MTYwODg3OTI0MiwgInJldHVybkJvZHkiOiJ7XCJmb29cIjokKHg6Zm9vKSwgXCJiYXJcIjokKHg6YmFyKSwgXCJtaW1lVHlwZVwiOiQobWltZVR5cGUpLCBcImhhc2hcIjokKGV0YWcpLCBcImtleVwiOiQoa2V5KSwgXCJmbmFtZVwiOiQoZm5hbWUpfSJ9";
        // test
        token = "HwFOxpYCQU6oXoZXFOTh1mq5ZZig6Yyocgk3BTZZ:Uh4lzaLRbUtcvn5E9KbN3SnCw_I=:eyJzY29wZSI6ImtvZG8tcGhvbmUtem9uZTAtc3BhY2UiLCJkZWFkbGluZSI6MTYwNzY2ODYxOSwgInJldHVybkJvZHkiOiJ7XCJmb29cIjokKHg6Zm9vKSwgXCJiYXJcIjokKHg6YmFyKSwgXCJtaW1lVHlwZVwiOiQobWltZVR5cGUpLCBcImhhc2hcIjokKGV0YWcpLCBcImtleVwiOiQoa2V5KSwgXCJmbmFtZVwiOiQoZm5hbWUpfSJ9";
        Map<String, String> params = new HashMap<String, String>();
        params.put("x:foo", "foo");
        params.put("x:bar", "bar");

        final UploadOptions options = new UploadOptions(params, null, true, new UpProgressHandler() {
            @Override
            public void progress(String key, double percent) {

                progressBar.setProgress((int)(percent * 100));
                String percentString = String.format("%.1f", percent * 100) + "%";
                progressTV.setText(percentString);

            }
        }, null);

        final Date startDate = new Date();
        uploadManager.put(mediaPath, "Android-demo", token, new UpCompletionHandler() {
            @Override
            public void complete(String key, ResponseInfo info, JSONObject response) {

                Date endDate = new Date();
                showMessage(info.toString() + "\r\n duration:" + (endDate.getTime() - startDate.getTime())/1000.0);
            }
        }, options);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if (resultCode == RESULT_OK){
            if (requestCode == PictureConfig.CHOOSE_REQUEST) {// 图片选择结果回调

                List<LocalMedia> mediaList = PictureSelector.obtainMultipleResult(data);
                if (mediaList != null && mediaList.size() > 0){
                    LocalMedia media = mediaList.get(0);
                    mediaPath = media.getPath();

                    if (mediaPath == null) {
                        return;
                    }

                    int mediaType = PictureMimeType.isPictureType(media.getPictureType());
                    if (mediaType == PictureConfig.TYPE_IMAGE){
                        showImage(mediaPath);
                    } else if (mediaType == PictureConfig.TYPE_VIDEO){
                        showVideo(mediaPath);
                    }
                }
            }
        }
    }

    private void showImage(String imagePath){
        if (imagePath == null || imagePath.length() == 0){
            return;
        }

        imageView.setVisibility(View.VISIBLE);
        videoView.setVisibility(View.INVISIBLE);
        videoView.clearFocus();
        videoView.pause();

        Bitmap bm = BitmapFactory.decodeFile(imagePath);
        imageView.setImageBitmap(bm);

    }

    private void showVideo(String videoPath){
        if (videoPath == null || videoPath.length() == 0){
            return;
        }

        imageView.setVisibility(View.INVISIBLE);
        videoView.setVisibility(View.VISIBLE);
        videoView.requestFocus();
        videoView.pause();

        MediaController mediaController = new MediaController(this);
        videoView.setMediaController(mediaController);
        videoView.setVideoPath(videoPath);
        videoView.start();
    }

    private void showMessage(String message){
        new AlertDialog.Builder(this)
                .setTitle("请求结果：")
                .setMessage(message)
                .setPositiveButton("确定", null)
                .show();
    }
}
