class Marathon {
    public static int findSlowest(int[] arr) {
        if (arr == null || arr.length == 0) return -1;
        if (arr.length == 1) return arr[0];
        int slowestValue = arr[0];
        int slowestIndex = 0;
        for (int i = 1; i < arr.length; i++) {
            if (arr[i] < slowestValue) {
                slowestValue = arr[i];
                slowestIndex = i;
            }
        }
        return slowestIndex;
    }
    public static int findSecondSlowest(int[] arr) {
        if (arr == null || arr.length == 0) return -1;
        if (arr.length == 1) return arr[0];
        int secondSlowestValue = arr[0];
        int secondSlowestIndex = 0;
        int slowestValue = arr[findSlowest(arr)];
        for (int i = 0; i < arr.length; i++) {
            if (slowestValue != arr[i]) {
                secondSlowestValue = arr[i];
                secondSlowestIndex = i;
                break;
            }
        }
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] < secondSlowestValue && arr[i] != slowestValue) {
                secondSlowestValue = arr[i];
                secondSlowestIndex = i;
            }
        }
        return secondSlowestIndex;
    }
    public static void main (String[] arguments) {
        String[] names = {
                "Elena", "Thomas", "Hamilton", "Suzie", "Phil", "Matt", "Alex",
                "Emma", "John", "James", "Jane", "Emily", "Daniel", "Neda",
                "Aaron", "Kate"
        };

        int[] times = {
                341, 273, 278, 329, 445, 402, 388, 275, 243, 334, 412, 393, 299,
                343, 317, 265
        };

        System.out.println(names[findSlowest(times)]);
        System.out.println(names[findSecondSlowest(times)]);
    }
} 