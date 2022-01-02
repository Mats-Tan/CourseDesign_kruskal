package Serverlet;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.net.URLEncoder;

public class ReDirectURL extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        this.doPost(req, resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        req.setCharacterEncoding("utf-8");
        String target = req.getParameter("search");
        String str = "https://www.baidu.com/s?wd="+URLEncoder.encode(target,"utf-8");// 这里需要两个参数对URL数据做字符到字节的编码转换
        resp.sendRedirect(str);
    }
}
