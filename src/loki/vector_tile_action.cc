// #include "loki/search.h"
#include "loki/worker.h"
// #include "tyr/serializers.h"
#include "baldr/json.h"
#include "baldr/rapidjson_utils.h"

using namespace valhalla;
using namespace valhalla::baldr;

namespace valhalla {
namespace loki {

void loki_worker_t::init_vector_tile(Api& request) {
  // parse_costing(request, true);
}

std::string loki_worker_t::serialize_vector_tile(Api& request) {

  std::cout << "serializeVectorTile" << std::endl;

  // if (request.options().format() == Options_Format_pbf)
    // return serializePbf(request);

  rapidjson::Document vector_tile_doc;
  vector_tile_doc.SetObject();
  auto& alloc = vector_tile_doc.GetAllocator();

  vector_tile_doc.AddMember("x", rapidjson::Value().SetInt(request.vector_tile().x()), alloc);
  vector_tile_doc.AddMember("y", rapidjson::Value().SetInt(request.vector_tile().y()), alloc);
  vector_tile_doc.AddMember("z", rapidjson::Value().SetInt(request.vector_tile().z()), alloc);

  return rapidjson::to_string(vector_tile_doc);
}

std::string loki_worker_t::vector_tile(Api& request) {
  // time this whole method and save that statistic
  auto _ = measure_scope_time(request);

  // correlate the various locations to the underlying graph
  // init_vector_tile(request);
  // auto locations = PathLocation::fromPBF(request.options().locations());
  // auto projections = loki::Search(locations, *reader, costing);
  // return tyr::serializevector_tile(request, locations, projections, *reader);
  
  // Access x, y, z from options
  auto options = request.options();
  if (!options.has_x() || !options.has_y() || !options.has_z()) {
    throw std::runtime_error("Missing x, y, or z parameter for vector tile request");
  }

  int32_t x = request.options().x();
  int32_t y = request.options().y();
  int32_t z = request.options().z();

  auto* mutable_vector_tile = request.mutable_vector_tile();
  mutable_vector_tile->set_x(x);
  mutable_vector_tile->set_y(y);
  mutable_vector_tile->set_z(z);

  return serialize_vector_tile(request);
}

} // namespace loki
} // namespace valhalla
