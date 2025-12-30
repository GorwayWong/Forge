package easy;

import java.util.ArrayList;

public class _682CalPoints {
    public int calPoints(String[] operations) {
        int res = 0;
        int curPoint = 0;
        ArrayList<Integer> points = new ArrayList<>();
        for (int i = 0; i < operations.length; i++) {
            curPoint = -1;
            switch (operations[i]) {
                case "+":curPoint = points.getLast()+points.get(points.size()-2);res+=curPoint;break;
                case "D":curPoint = points.getLast()*2;res+=curPoint;break;
                case "C":res-=points.getLast();points.removeLast();break;
                default:curPoint = Integer.parseInt(operations[i]);res+=curPoint;break;
            }
            if(curPoint!=-1){
                points.add(curPoint);
            }
        }
        return res;
    }
}
