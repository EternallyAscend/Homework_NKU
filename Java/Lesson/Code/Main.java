import java.util.*;
import java.lang.*;

class FormatPath {
    Vector<String> path;
    String input;
    String output;

    public FormatPath(String s) {
        this.input = s.replace('\\','/');
        this.path = new Vector<String>();
        this.output = "";
        try {
            this.deal();
        } catch (Exception e) {
            this.output = "Value Error";
        }
    }

    private void deal() throws Exception {
        if (this.input.length() == 0) {
            throw new Exception("Empty.");
        }

        int cursor;
        int start;
        int end;
        start = 0;
        end = 0;
        if (this.input.length() > 1) {
            if (this.input.charAt(0) == '/') {
                this.output = "/";
            }
            for (cursor = 1; cursor < this.input.length(); cursor++) {
                switch (this.input.charAt(cursor - 1)){
                    case '/':
                        start = cursor;
                        break;
                    case '.':
                        if (this.input.charAt(cursor) == '.') {
                            if (this.path.isEmpty()) {
                                throw new Exception("Wrong Expression.");
                            }
                            this.path.remove(this.path.size() - 1);
                        }
                        break;
                    default:
                        if (this.input.charAt(cursor) == '/') {
                            end = cursor;
                            this.path.add(this.input.substring(start, end));
                        }
                        break;
                }

            }
            if (start < this.input.length() && this.input.charAt(this.input.length() - 1) != '/') {
                if (!this.input.substring(start).equals("/") && !this.input.substring(start).equals(".")) {
                    this.path.add(this.input.substring(start));
                }
                if (this.input.substring(start).equals("..")) {
                    if (this.path.isEmpty()) {
                        throw new Exception("Wrong Expression.");
                    }
                    this.path.remove(this.path.size() - 1);
                }
            }
        } else {
            if (!this.input.equals(".")) {
                this.path.add(this.input);
            }
        }

        for (cursor = 0; cursor < this.path.size(); cursor++) {
            this.output += this.path.get(cursor) + "/";
        }

        if (this.path.size() != 0) {
            this.output = this.output.substring(0, this.output.length() - 1);
        }

    }

    public String getOutput() {
        return this.output;
    }
}

public class Main {
    public static void main(String []args) {
        System.out.println("Java 2020.");
        Scanner scanner = new Scanner(System.in);
        while (scanner.hasNext()) {
            String string = scanner.nextLine();
            FormatPath path = new FormatPath(string);
            System.out.println(path.getOutput());
        }
    }
}

// Powered by Intellij IDEA Community Edition 2020.1.

//./jisuanke\\./suantou/../bin/
//..
///\./\.\/.\/

//测评信息
//        ================================================
//        测评用例 1：答案错误 [165.000 毫秒，10896 KB]
//        用例输入：
//        a\\B
//        \\\\A\\\\B
//        \\\\A\\\\B
//
//        用例正确输出：
//        a/B
//        /A/b
//        /A/B
//
//        你的输出：
//        a
//        /A
//        /A
//        ---------------------------
//        测评用例 2：答案错误 [143.000 毫秒，10900 KB]
//        ---------------------------
//        测评用例 3：答案错误 [129.000 毫秒，10908 KB]
//        ---------------------------
//        测评用例 4：答案错误 [152.000 毫秒，10932 KB]
//        ---------------------------
//        测评用例 5：答案错误 [159.000 毫秒，10880 KB]
//        ---------------------------
//        测评用例 6：答案错误 [155.000 毫秒，10908 KB]
//
//        结果
//        ================================================
//        共 6 组测评用例，通过 0 组。
//
//        /
//        .
//        /.
//        1/..
//        1/../
//        /1/..
//        /1/../
//
//        用例正确输出：
//        /
//
//        /
//
//
//        /
//        /
//
//        你的输出：
//        /
//        .
//        /
//
//
//        /
//        /