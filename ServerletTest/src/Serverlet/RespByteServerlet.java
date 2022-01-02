package Serverlet;

import javax.servlet.ServletException;
import javax.servlet.ServletOutputStream;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.PrintStream;

/*设置字节型响应*/
public class RespByteServerlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        this.doPost(req, resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        //读取图片到serverlet
        File file = new File("H:\\摄影\\Pictures\\JPG\\风光\\_DSC0057.JPG");
        FileInputStream fis = new FileInputStream(file);
        byte[] buff = new byte[fis.available()];
        fis.read(buff);

        //设置响应类型
        resp.setContentType("image/jpeg");
        ServletOutputStream outputStream = resp.getOutputStream();
        outputStream.write(buff);
    }
}
