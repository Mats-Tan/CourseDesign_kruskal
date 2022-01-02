package Serverlet;

import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

public class GetBaseInfoServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        this.doPost(req, resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        resp.setContentType("text/html;charset=utf-8");

        ServletContext servletContext = this.getServletContext();
        String servletInfo = servletContext.getServerInfo();//获取容器名称
        int majorVersion = servletContext.getMajorVersion();//获取主版本号
        int minorVersion = servletContext.getMinorVersion();//获取副版本号

        PrintWriter out = resp.getWriter();
        out.println("<!DOCTYPE HTML PUBLIC '-//W3C//DTD HTML 4.0 Transitional//EN'>");
        out.println("<HTML>");
        out.println("<HEAD><TITLE> ITBZ </TITLE></HEAD>");
        out.println("<BODY>");
        out.println("servletName:"+servletInfo+"<br/>");
        out.println("版本号:"+majorVersion+"."+minorVersion);
        out.println("</BODY>");
        out.println("</HTML>");
        out.flush();
        out.close();

    }
}
