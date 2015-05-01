// this will strip all severity level less than 1. Must be defined before include
//#define GOOGLE_STRIP_LOG 1
#include <glog/logging.h>
#include <string>
#include <sstream>
#include <memory>

namespace
{
std::string fancyLogging()
{
  static int counter = 0;
  counter++;
  std::stringstream info;
  info << "This is the " << counter << "th run!";
  return info.str();
}
void fakeFailureFunction()
{ }
}

int main(int argc, char *argv[])
{
  google::InitGoogleLogging(argv[0]);
//  google::InstallFailureFunction(&fakeFailureFunction);

  // DIFFERENT SEVERITY
  // - use flag *minloglevel*(default: ERROR, 2) to control severity logging
  //   level greater than or equal to minloglevel will be logged
  LOG(INFO) << "This is an INFO, severity level 0";
  LOG(WARNING) << "This is a WARNING, severity level 1";
  LOG(ERROR) << "This is an ERROR, severity level 2";
//  LOG(FATAL) << "This is a FATAL, which kills your program.";

  // CONDITIONAL
  LOG_IF(INFO, 3>1) << "This will be logged(3>1).";
  LOG_IF(INFO, 1>3) << "This will be not be logged(1>3).";
  for(int i=1; i<100; i++)
  {
    LOG_FIRST_N(INFO, 5) << "In the loop the first 5: "
                         << google::COUNTER << "th logging";
    LOG_EVERY_N(INFO, 30) << "In the loop every 30: "
                          << google::COUNTER <<"th logging.";
    LOG_IF_EVERY_N(INFO, (i>50), 30) << "In the loop every 30 after 50: "
                                     << google::COUNTER <<"th logging.";
  }
  DLOG(INFO) << "Only in debug model(when NDEBUG macro not defined)";

  // CHECK
  // - failed check will KILL your program
  // - the right hand expression in only evaluated when check fails
  // simple check
  CHECK_EQ(1, 1) << fancyLogging();
//  CHECK(1==2) << "This is solid math.";
//  int *p = NULL;
//  CHECK_NOTNULL(p);
  std::shared_ptr<std::string> sp = std::make_shared<std::string>("some");
  CHECK(sp) << "Empty shared pointer";
  // check string
  CHECK_STRNE("UpPer", "UPPER") << fancyLogging();
  CHECK_STRCASEEQ("lower", "LOWER") << fancyLogging();
//  CHECK_STREQ("UpPer", "UPPER") << fancyLogging();
//  CHECK_STRCASENE("lower", "LOWER") << fancyLogging();
  // check double
  CHECK_DOUBLE_EQ(10.0/3, 10.0/3);
  CHECK_NEAR(1.1, 1.3, 0.3);
  // debug check
  DCHECK(1==2) << "This kills your program in debug but nothing happens for release.";

  // VERBOSE LOGGING
  // - verbose log is in severity level INFO, thus can be suppressed along with INFO
  // - usually we do not need verbose logging
  // - the output level is controlled by flag *v*(defaut zero)
  //   where level smaller than or equal to v will be logged
  // - normally we choose small positive numbers
  VLOG(1) << "This is verbose level 1 logging.";
  VLOG(2) << "This is verbose level 2 logging.";
  // if stream is not enough for you
  if(VLOG_IS_ON(2))
    fancyLogging();
  // you can also have conditional verbose logging
  VLOG_IF(1, 1<2) << "conditional verbose logging.";
  // and debug log
  DVLOG(0) << "A zero level debug only log.";
  return 0;
}
