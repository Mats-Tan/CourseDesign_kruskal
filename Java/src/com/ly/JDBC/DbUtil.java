package com.ly.JDBC;

import java.io.IOException;
import java.io.InputStream;
import java.sql.*;
import java.util.Properties;

public class DbUtil {
    private String user;
    private String password;
    private String url;
    private String driverClass;
    private Connection conn;
    private Statement statement;

    public DbUtil() {
        //1 读取配置文件中4个基本信息
        InputStream is =
                JDBCUtil.class.getClassLoader().getResourceAsStream("jdbc.properties");
        Properties pros = new Properties();
        try {
            pros.load(is);
        } catch (IOException e) {
        }
        user = pros.getProperty("user");
        password = pros.getProperty("password");
        url = pros.getProperty("url");
        driverClass = pros.getProperty("driverClass");
        //2 加载驱动
        try {
            Class.forName(driverClass);
        } catch (ClassNotFoundException e) {
        }
        this.dbConnection();
    }


    private Connection dbConnection(){
        //3 获取链接
        try {
            conn = DriverManager.getConnection(url,user,password);
            statement = conn.createStatement();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return conn;
    }

    public void CloseConnection(Connection conn) throws SQLException {
        if(conn!=null)
            conn.close();
    }

    public Connection getConn() {
        return conn;
    }

    public Statement getStatement(){
        return statement;
    }

    public ResultSet getResultSet(String sql){
        ResultSet rs = null;
        try {
            rs = statement.executeQuery(sql);
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return rs;
    }
}
