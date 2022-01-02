package com.ly.GUI;


import com.ly.Graph.Province;
import com.ly.JDBC.DbUtil;
import com.ly.Web.CityUtil;
import com.ly.Graph.Graph;
import sun.plugin2.message.SetChildWindowHandleMessage;

import java.awt.BorderLayout;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.*;
import javax.swing.*;
import javax.swing.event.PopupMenuEvent;
import javax.swing.event.PopupMenuListener;

/*
 * 演示JComboBox的基本用法，以及事件响应
 */
public class JComboBoxBasicUseDemo extends JFrame {
    private static final long serialVersionUID = -8161981948004677531L;
    int DEFAULT_WIDTH = 500;
    int DEFAULT_HEIGHT = 100;
    private JLabel label;
    private JLabel textCity;
    private JList jl1;
    private JList jl2;
    private JComboBox<String> faceCombo;
    private static final int FONTSIZE = 15;
    private static boolean flag = false;
    private static Process process = null;
    @SuppressWarnings("unused")
    public JComboBoxBasicUseDemo() throws SQLException {
        DbUtil db = new DbUtil();
        List<Province> provinces = new LinkedList<>();
        String id = null;
        final Graph[] graph = {new Graph()};

        ResultSet rs = db.getResultSet("SELECT id,`name` FROM `detaillevel` where deep=0;");
        //loading <id,province>set into program;
        while (rs.next()) {
            provinces.add(new Province(rs.getString(1), rs.getString(2)));
        }
        /*jl1 = new JList();
        jl1.setFixedCellWidth(100);
        jl1.setFont(new Font("Serif",Font.PLAIN,FONTSIZE));*/

        setTitle("我的程序");
        setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
        //添加label
        label = new JLabel("各省理论最小生成树与实际铁路数据的最小生成树对比图形化");
        label.setFont(new Font("微软雅黑", Font.PLAIN, 30));
        add(label, BorderLayout.NORTH);

        textCity = new JLabel();
        //actionListener
        ActionListener actionListener = new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                if (e.getSource() instanceof JComboBox) {
                    @SuppressWarnings({"unchecked", "rawtypes"})
                    JComboBox<String> comboBox = (JComboBox) e.getSource();
                    String fontName = comboBox.getSelectedItem().toString();
                    label.setFont(new Font(fontName, Font.PLAIN, FONTSIZE));
                    System.out.printf("%s%n", "actionPerformed called");
                }
            }
        };
        //popupMenuListener
        PopupMenuListener popupMenuListener = new PopupMenuListener() {
            @Override
            public void popupMenuCanceled(PopupMenuEvent e) {
                System.out.println("下拉菜单取消");
            }

            @SuppressWarnings("unchecked")
            @Override
            public void popupMenuWillBecomeInvisible(PopupMenuEvent e) {
                System.out.println("下拉菜单合上");
                JComboBox<String> source = (JComboBox<String>) e.getSource();
            }

            @Override
            public void popupMenuWillBecomeVisible(PopupMenuEvent e) {
                System.out.println("下拉菜单弹出");
            }
        };
        //itemListener
        ItemListener itemListener = new ItemListener() {
            @Override
            public void itemStateChanged(ItemEvent arg0) {
                // TODO Auto-generated method stub
                if (ItemEvent.SELECTED == arg0.getStateChange()) {
                    String selectedItem = arg0.getItem().toString();
                    label.setFont(new Font(selectedItem, Font.PLAIN, FONTSIZE));
                    System.out.printf("new selected item : %s%n", selectedItem);
                    if (flag) {
                        for (int i = 0; i < provinces.size(); i++) {
                            if (provinces.get(i).isSameProvince(selectedItem)) {
                                if((graph[0] = Graph.minTreeLoading(provinces.get(i).getId()))!=null){
                                    String str = graph[0].getPositions().toString();
                                    /*jl1.setListData(graph[0].getPositions().toArray());*/
                                    textCity.setText(graph[0].getPositions().toString());
                                    textCity.setFont(new Font("微软雅黑", Font.PLAIN, FONTSIZE));
                                    add(textCity, BorderLayout.SOUTH);
                                    process = openExe("E:\\CourseDesign\\bin\\Graph.exe D:\\src\\res\\ALL.csv,D:\\src\\res\\TrainRoad.csv,1920,1080");
                                    flag = false;
                                }
                            }
                        }
                    }
                }
                if (ItemEvent.DESELECTED == arg0.getStateChange()) {
                    closeExe(process);
                    flag = true;
                    textCity.setText(null);
                    String selectedItem = arg0.getItem().toString();
                    System.out.printf("deselected item : %s%n", selectedItem);
                }
            }
        };
        //添加一个JComboBox
        faceCombo = new JComboBox<String>();
        faceCombo.setEditable(true);
        //faceCombo.addActionListener(actionListener);
        //faceCombo.addPopupMenuListener(popupMenuListener);
        faceCombo.addItemListener(itemListener);
        faceCombo.setEnabled(true);

        rs = db.getResultSet("SELECT `name` FROM `detaillevel` where deep=0;");
        while (rs.next()) {
            faceCombo.addItem(rs.getString(1));
        }
        faceCombo.setLightWeightPopupEnabled(true);
        add(faceCombo, BorderLayout.NORTH);
        faceCombo.setSelectedIndex(-1);

    }

    public static Process openExe(String path) {
        final Runtime runtime = Runtime.getRuntime();
        Process process = null;

        try {
            process = runtime.exec(path);
        } catch (final Exception e) {
            System.out.println("Error exec!");
        }
        return process;
    }

    public static boolean closeExe(Process process) {
        if (process != null) {
            process.destroy();
            return true;
        }
        return false;
    }

    public static void main(String[] args) throws SQLException {
        // TODO Auto-generated method stub
        //创建窗体并指定标题
        JComboBoxBasicUseDemo frame = new JComboBoxBasicUseDemo();
        //关闭窗体后退出程序
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        //自动适配所有控件大小
        //frame.pack();
        //设置窗体位置在屏幕中央
        frame.setLocationRelativeTo(null);
        //显示窗体
        frame.setVisible(true);
    }
}