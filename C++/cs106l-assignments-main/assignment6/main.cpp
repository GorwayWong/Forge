/*
 * CS106L Assignment 6: Explore Courses
 * Created by Haven Whitney with modifications by Jacob Roberts-Baca and Fabio
 * Ibanez.
 */

#include <algorithm>
#include <type_traits>
#include <vector>
#include <optional>

#include "autograder/utils.hpp"

/**
 * A course. This should be familiar from Assignment 1!
 */
struct Course
{
  std::string title;
  std::string number_of_units;
  std::string quarter;

  /**
   * You don't have to ignore this anymore! We're defining the `==` operator for
   * the Course struct.
   */
  bool operator==(const Course& other) const
  {
    return title == other.title && number_of_units == other.number_of_units &&
           quarter == other.quarter;
  }
};

class CourseDatabase
{
public:
  CourseDatabase(std::string filename)
  {
    auto lines = read_lines(filename);
    std::transform(lines.begin(),
                   lines.end(),
                   std::back_inserter(courses),
                   [](std::string line) {
                     auto parts = split(line, ',');
                     return Course{ parts[0], parts[1], parts[2] };
                   });
  }

  /**
   * Finds a course in the database with the given title, if it exists.
   * @param course_title The title of the course to find.
   * @return You will need to figure this out!
   */
  std::optional<Course> find_course(std::string course_title)
  {
    for (auto it = courses.begin(); it != courses.end(); it++)
    {
      if ((*it).title == course_title){
        return *it;
      }
    }
    return {};
  }

private:
  std::vector<Course> courses;
};

int
main(int argc, char* argv[])
{
  static_assert(
    !std::is_same_v<std::invoke_result_t<decltype (&CourseDatabase::find_course), 
                      CourseDatabase, std::string>,
                    FillMeIn>,
    "You must change the return type of CourseDatabase::find_course to "
    "something other than FillMeIn.");

  if (argc == 2) {
    CourseDatabase db("autograder/courses.csv");
    auto course = db.find_course(argv[1]);

    // 先用and_then转换成装别的类型的std::optional<std::string>, 不要用transform因为它把返回的optional自动包装成optional<optional<string>>
    // std::string output = course.and_then([](Course course) -> std::optional<std::string>{
    //   std::optional<std::string> str;
    //   str = "Found course: " + course.title +"," + course.number_of_units +"," + course.quarter + "\n";
    //   return str;
    // })
    // .or_else([]() -> std::optional<std::string> {
    //   std::optional<std::string> str;
    //   str = "Course not found.\n";
    //   return str;
    // })
    // .value();

    //用transform时：
    std::string output = course.transform([](Course course) -> std::string{
      std::string str;
      str = "Found course: " + course.title +"," + course.number_of_units +"," + course.quarter + "\n";
      return str;
    })
    .or_else([]() -> std::optional<std::string> {
      std::optional<std::string> str;
      str = "Course not found.\n";
      return str;
    })
    .value();

    /********************************************************
     DO NOT MODIFY ANYTHING BELOW THIS LINE PLEASE
    ********************************************************/

    std::cout << output << std::endl;
    return 0;
  }
  
  return run_autograder();
}