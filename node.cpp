#include "node.h"
#include <sstream>
#include <memory>
using namespace std;

bool EmptyNode::Evaluate(const Date& date_, const string& event_) const
{
	return true;
}

LogicalOperationNode::LogicalOperationNode(const LogicalOperation& logical_operation, const shared_ptr<const Node>& left, const shared_ptr<const Node>& right) : logical_operation_(logical_operation), left_node_(left), right_node_(right) {}

bool LogicalOperationNode::Evaluate(const Date& date_, const string& event_) const
{
	if (logical_operation_ == LogicalOperation::And) return left_node_->Evaluate(date_, event_) && right_node_->Evaluate(date_, event_);
	else return left_node_->Evaluate(date_, event_) || right_node_->Evaluate(date_, event_);
}

DateComparisonNode::DateComparisonNode(const Comparison& comparator, const Date& date) : comparator_(comparator), self_date_(date)
{
}

bool DateComparisonNode::Evaluate(const Date& date_, const string& event_) const
{
	switch (comparator_)
	{
	case Comparison::Equal: return date_ == self_date_;
	case Comparison::NotEqual: return date_ != self_date_;
	case Comparison::Greater: return date_ > self_date_;
	case Comparison::LessOrEqual: return date_ <= self_date_;
	case Comparison::GreaterOrEqual: return date_ >= self_date_;
	case Comparison::Less: return date_ < self_date_;
	}
}

EventComparisonNode::EventComparisonNode(const Comparison& comparator, const string& event_) : comparator_(comparator), self_event_(event_)
{
}

bool EventComparisonNode::Evaluate(const Date& date_, const string& event_) const
{
	switch (comparator_)
	{
	case Comparison::Equal: return event_ == self_event_;
	case Comparison::NotEqual: return event_ != self_event_;
	case Comparison::Greater: return event_ > self_event_;
	case Comparison::LessOrEqual: return event_ <= self_event_;
	case Comparison::GreaterOrEqual: return event_ >= self_event_;
	case Comparison::Less: return event_ < self_event_;
	}
}
