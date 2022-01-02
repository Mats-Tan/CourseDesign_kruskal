package Serverlet;

import javax.servlet.ServletException;
import javax.servlet.ServletOutputStream;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.net.URLEncoder;


/**
 * 文件下载
 */
public class FileDownLoad extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        this.doPost(req, resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
//      // 先知道下载哪个文件
            // 读入 servlet
        req.setCharacterEncoding("utf-8");
        String path = req.getParameter("path");
        File file = new File(path);
        FileInputStream fis = new FileInputStream(file);
        byte[] buff = new byte[fis.available()];
        fis.read(buff);
        resp.setCharacterEncoding("utf-8");
        // 在响应中添加附加信息
        resp.setHeader("Content-Disposition","attachment;filename="+ URLEncoder.encode(file.getName(),"utf-8"));
        // 拿字节输出流
        ServletOutputStream out = resp.getOutputStream();
        out.write(buff);
        out.flush();
        out.close();
    }
}
