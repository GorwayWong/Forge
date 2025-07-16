public class FooCorporation {
    public double calculateSalary(double basePay, int hoursWorked) {
        if (hoursWorked > 60) {
            System.out.println("The hours worked is greater than 60");
            return -1;
        }
        if (basePay < 8.00) {
            System.out.println("Base pay is less than 8.00");
            return -1;
        }
        if (hoursWorked <= 40) {
            return basePay*hoursWorked;
        } else {
            return basePay*40 + (hoursWorked-40)*1.5*basePay;
        }
    }

    public static void main(String[] args) {
        System.out.println(new FooCorporation().calculateSalary(7.50, 35));
        System.out.println(new FooCorporation().calculateSalary(8.20, 47));
        System.out.println(new FooCorporation().calculateSalary(10.0, 73));
    }
}
