package com.ly.Web;

import com.ly.JDBC.DbUtil;
import org.apache.http.HttpEntity;
import org.apache.http.client.methods.CloseableHttpResponse;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClients;
import org.apache.http.util.EntityUtils;

import java.io.IOException;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class CityUtil {
    public String[][] getCity() throws Exception{
        String url="https://kyfw.12306.cn/otn/resources/js/framework/station_name.js?station_version=1.9222";

        HttpGet httpget=new HttpGet(url);
        CloseableHttpClient httPclient= HttpClients.createDefault();
        CloseableHttpResponse Response=httPclient.execute(httpget);
        HttpEntity entity=Response.getEntity();
        String result= EntityUtils.toString(entity,"utf-8");
        //System.out.println("请求结果"+result);
        int l1=result.indexOf("'");
        int l2=result.length();
        String city=result.substring(l1+1, l2);
        String[] c=city.split("@");
        //导入二维数组
        int l=c.length-1;
        String[][] str=new String[l][2];
        for(int i=1;i<c.length;i++) {
            String[] cc=c[i].split("[|]");
            //System.out.println(cc[1]+" "+cc[2]);
            str[i-1][0]=cc[1];
            str[i-1][1]=cc[2];
        }
        return str;
    }

    public void addInDB(DbUtil db,String name,String code){
        String sql = "INSERT INTO station \n" +
                "(station_name,station_code)\n" +
                "VALUES\n" +
                "(\"" +
                name +
                "\",\"" +
                code +
                "\");";
        Connection conn = db.getConn();
        Statement statement = null;
        try {
             statement= conn.createStatement();
            statement.execute(sql);
        } catch (SQLException e) {
            e.printStackTrace();
        }finally {
            try {
                statement.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }

    public static void main(String[] args) throws Exception {
        CityUtil cu= new CityUtil();
        DbUtil db = new DbUtil();
        String[][] arrs = cu.getCity();
        for(int i=0;i<arrs.length;i++){
            cu.addInDB(db,arrs[i][0],arrs[i][1]);
//            System.out.println(arrs[i][0]+"-"+arrs[i][1]);
        }
        db.CloseConnection(db.getConn());
//        System.out.println("一共"+i+"条数据");
    }
}
