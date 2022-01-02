package Serverlet;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.*;

public class ServerletDemo extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        super.doGet(req, resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        resp.setCharacterEncoding("utf-8");
        req.setCharacterEncoding("utf-8");
        String username = req.getParameter("username");
        System.out.println(username);
        String[] list = req.getParameterValues("userlike");
        Enumeration<String> parameterNames = req.getParameterNames();
        List<String> keys = new ArrayList<>();
        Map<String, String[]> parameterMap = req.getParameterMap();
        while(parameterNames.hasMoreElements()) {
             keys.add(parameterNames.nextElement());
        }
        PrintWriter out = resp.getWriter();
        out.println("<!DOCTYPE HTML PUBLIC '-//W3C//DTD HTML 4.0 Transitional//EN'>");
        out.println("<HTML>");
        out.println("<HEAD><TITLE> ITBZ </TITLE></HEAD>");
        out.println("<BODY>");
        out.println("username:"+username+"<br/>");
        out.println("userlike:"+ Arrays.asList(list)+"<br/>");
        Iterator<Map.Entry<String, String[]>> iterator = parameterMap.entrySet().iterator();
        while(iterator.hasNext()){
            Map.Entry<String, String[]> entry = iterator.next();
            out.println("Keys:"+entry.getKey()+" Value:"+Arrays.asList(entry.getValue())+"<br/>");
        }
//        out.println("keys:"+ keys+"<br/>");
        out.println("</BODY>");
        out.println("</HTML>");
        out.flush();
        out.close();
    }
}
